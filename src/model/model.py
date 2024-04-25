import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, MultiLabelBinarizer

from keras import config
from keras.models import Sequential
from keras.layers import LSTM, Dense, Dropout, Input

config.disable_interactive_logging()

# Reshape the input data for LSTM
timesteps = 3  # Number of timesteps (days) to consider for each input sequence
max_exercises = 10

# Load and preprocess the health data
polar_table = pd.read_csv('polar_user_data.csv')
health_data = polar_table[['date', 'steps', 'active_calories', 'max_hr', 'ae_t', 'light_sleep', 'deep_sleep']]
activities = polar_table[['date', *[f'exercise{i}' for i in range(1, 11)]]]

# Scale the features using MinMaxScaler
scaler = MinMaxScaler()
X = scaler.fit_transform(health_data.drop('date', axis=1))

# Perform multi-label binarization for the exercise columns
mlb = MultiLabelBinarizer()
y = mlb.fit_transform(
    activities[[f'exercise{i}' for i in range(1, max_exercises + 1)]].apply(lambda x: [i for i in x if str(i) != "nan"],
                                                                            axis=1))
X = np.array([X[i - timesteps:i] for i in range(timesteps, X.shape[0])])
y = y[timesteps:]

# Define the LSTM model
model = Sequential()
model.add(Input(shape=(timesteps, X.shape[2])))
model.add(LSTM(units=128, return_sequences=True))
model.add(Dropout(0.2))
model.add(LSTM(units=64))
model.add(Dropout(0.2))
model.add(Dense(units=64, activation='relu'))
model.add(Dense(y.shape[1], activation='sigmoid'))
model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(X, y, epochs=50, batch_size=32, validation_split=0.2)

# Get the last 3 days' data from the health_data DataFrame
last_3_days_data = health_data.tail(timesteps).drop('date', axis=1)
scaled_last_3_days_data = scaler.transform(last_3_days_data)
X_test = scaled_last_3_days_data.reshape((1, timesteps, scaled_last_3_days_data.shape[1]))

# Make predictions for the next day based on the health data of the last 3 days
prediction = model.predict(X_test)

# Get the predicted exercise names for the next day
predicted_exercise_names = mlb.inverse_transform(prediction > 0.5)[0]

prediction_file = open("prediction.txt", "w")
prediction_file.write(' '.join(predicted_exercise_names))
prediction_file.close()
