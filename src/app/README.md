# App

Весь модуль представлен классом PolarApp со следующими методами:

#### 1. Activate

В этой функции происходит инстанцирование объекта типа Crow::SimpleApp, который имитирует поведение сервера.

#### 2. Authorize

Здесь происходит авторизация пользователя в приложении.

#### 3. UpdateAccessConfig

Небольшая функция для работы с файлом config.yaml (в него сохраняется user-id и access-token).

#### 4. ProcessData

Здесь описана верхнеуровневая логика работы с данными пользователя. То есть в этой фукнции мы получаем всю доступную
информацию с серверов Polar, обновляем БД, запускаем модель и выставляем результаты модели в Google Calendar