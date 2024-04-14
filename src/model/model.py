import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, LabelEncoder
from keras.models import Sequential
from keras.layers import LSTM, Dense, Dropout, Input

# Загружаем данные о здоровье + активность, тренировка которая была сегодня
polar_table = pd.read_csv('polar_user_data.csv')
health_data = polar_table[['date', 'steps', 'active_calories', 'max_hr', 'ae_t', 'light_sleep', 'deep_sleep']]
activities = polar_table[['date', 'exercise1']]

activities['exercise1'] = activities['exercise1'].fillna('stay at home')

# Скейлим фичи с помощью MinMaxScaler
scaler = MinMaxScaler()
X = scaler.fit_transform(health_data.drop('date', axis=1))

# Perform label encoding for the activity column
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(activities['exercise1'])

timesteps = 3  # кол-во дней, на которые мы смотрим для того, чтобы сделать prediction
# (то есть будем считать, что на наш выбор завтра влияет наше состояние не только за сегодня, но и за два дня до этого)
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
model.add(Dense(len(label_encoder.classes_), activation='softmax'))
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

model.fit(X, y, epochs=50, batch_size=32, validation_split=0.2)

last_3_days_data = health_data.tail(timesteps).drop('date', axis=1)
scaled_last_3_days_data = scaler.transform(last_3_days_data)
X_test = scaled_last_3_days_data.reshape((1, timesteps, scaled_last_3_days_data.shape[1]))

# предсказание активности на следующий день
prediction = model.predict(X_test)
predicted_label = label_encoder.inverse_transform(np.argmax(prediction, axis=1))[0]

print(f"Predicted activity for the next day: {predicted_label}")
