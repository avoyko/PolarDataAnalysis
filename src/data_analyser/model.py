import numpy as np

from tensorflow.python import keras
from keras.models import Sequential
from keras.layers import LSTM, Dense, Conv1D, MaxPooling1D, Flatten, TimeDistributed
from keras.utils import to_categorical
from sklearn.ensemble import RandomForestClassifier
from keras_tuner import RandomSearch
from keras_tuner.engine.hyperparameters import HyperParameters

# List of activity options
activity_options = ['swimming', 'jogging', 'walking', 'cycling', 'gym exercises', 'stay at home']
num_activities = len(activity_options)

# Generate random data
num_samples = 1000
sequence_length = 30
num_features = 5  # e.g., heart rate, sleep hours, stress level, and other schedule features

# Generate random input data
X = np.random.rand(num_samples, sequence_length, num_features)

# Generate random target activities
activities = np.random.randint(num_activities, size=num_samples)
y = to_categorical(activities, num_classes=num_activities)

# Split data into train and test sets
train_size = int(num_samples * 0.8)
X_train, y_train = X[:train_size], y[:train_size]
X_test, y_test = X[train_size:], y[train_size:]

# Reshape input data for CNN
X_train = X_train.reshape(X_train.shape[0], X_train.shape[1], X_train.shape[2], 1)
X_test = X_test.reshape(X_test.shape[0], X_test.shape[1], X_test.shape[2], 1)


# Hyperparameter tuning function
def build_model(hp):
    model = Sequential()
    model.add(TimeDistributed(Conv1D(filters=hp.Int('conv_filters', min_value=32, max_value=128, step=16),
                                     kernel_size=hp.Int('conv_kernel_size', min_value=2, max_value=5),
                                     activation='relu'), input_shape=(None, X_train.shape[2], 1)))
    model.add(TimeDistributed(MaxPooling1D(pool_size=2)))
    model.add(TimeDistributed(Flatten()))
    model.add(LSTM(hp.Int('lstm_units', min_value=32, max_value=128, step=16), return_sequences=True))
    model.add(LSTM(hp.Int('lstm_units', min_value=32, max_value=128, step=16)))
    model.add(Dense(num_activities, activation='softmax'))
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    return model


# Hyperparameter tuning
tuner = RandomSearch(build_model, objective='val_accuracy', max_trials=5, directory='tuner_results',
                     project_name='activity_prediction')
tuner.search(X_train, y_train, epochs=10, validation_data=(X_test, y_test))

# Get the best hyperparameters
best_hps = tuner.get_best_hyperparameters(num_trials=1)[0]

# Build the model with the best hyperparameters
model = tuner.hypermodel.build(best_hps)

# Predict activities for the next day
# Assuming health data for the next day is the average of the previous 3 days
next_day_health_data = np.mean(X_test[-3:, :, :], axis=0)
next_day_health_data = next_day_health_data.reshape(1, sequence_length, num_features)

# Predict activities using the neural network
nn_next_day_activities_probs = model.predict(next_day_health_data)[0]
nn_next_day_activity_idx = np.argmax(nn_next_day_activities_probs)
nn_next_day_activity = activity_options[nn_next_day_activity_idx]
print(f"Predicted activity (NN) for the next day: {nn_next_day_activity}")

# Ensemble method: Random Forest
rf_model = RandomForestClassifier(n_estimators=100)
rf_model.fit(X_train.reshape(X_train.shape[0], -1), np.argmax(y_train, axis=1))
next_day_health_data_flat = next_day_health_data.reshape(1, -1)
rf_next_day_activity_idx = rf_model.predict(next_day_health_data_flat)[0]
rf_next_day_activity = activity_options[rf_next_day_activity_idx]
print(f"Predicted activity (RF) for the next day: {rf_next_day_activity}")
