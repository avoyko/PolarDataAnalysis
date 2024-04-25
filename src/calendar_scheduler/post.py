import os.path
import sys
import webbrowser

from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ["https://www.googleapis.com/auth/calendar"]


def schedule():
    creds = None
    if os.path.exists("../calendar_scheduler/token.json"):
        creds = Credentials.from_authorized_user_file("../calendar_scheduler/token.json", SCOPES)
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file("../calendar_scheduler/credentials.json", SCOPES)
            creds = flow.run_local_server(port=0, open_browser=False, )
        with open("../calendar_scheduler/token.json", "w") as token:
            token.write(creds.to_json())
    try:
        event_name = sys.argv[1]
        start_date, end_date = sys.argv[2], sys.argv[3]
        service = build("calendar", "v3", credentials=creds)
        event = {'summary': event_name, 'start': {'dateTime': start_date}, 'end': {'dateTime': end_date}}
        event = service.events().insert(calendarId='primary', body=event).execute()

    except HttpError as error:
        pass


if __name__ == "__main__":
    schedule()
