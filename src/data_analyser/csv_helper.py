
import csv
import os

heartrate_file: str = "/datasets/FitabaseData/heartrate_seconds_merged.csv"
sleep_file: str = "/datasets/FitabaseData/sleepDay_merged.csv"
write_file: str = "/datasets/FitabaseData/final_data.csv"
base_file: str = "/datasets/FitabaseData/dailyActivity_merged.csv"


class CSVhelper(object):
    def __init__(self) -> None:
        pass

    def retrieve_heartrate_data(self, read_file_path: str) -> list:
        users_data = {}
        with open(read_file_path, "r") as csvfile:
            text = csv.reader(csvfile)
            for row in text:
                user_id = self.get_user_id(row)
                if (user_id == 'Id'):
                    continue
                date = self.get_date(row)
                heartrate = self.get_heartrate(row)
                if user_id not in users_data:
                    users_data[user_id] = dict()
                if date not in users_data[user_id]:
                    users_data[user_id][date] = [heartrate, heartrate]
                users_data[user_id][date][0] = min(
                    users_data[user_id][date][0], heartrate)
                users_data[user_id][date][1] = max(
                    users_data[user_id][date][1], heartrate)
        return users_data

    def retrieve_sleep_data(self, read_file_path: str) -> list:
        users_data = {}
        with open(read_file_path, "r") as csvfile:
            text = csv.reader(csvfile)
            for row in text:
                user_id = self.get_user_id(row)
                if (user_id == 'Id'):
                    continue
                date = self.get_date(row)
                total_minutes_asleep = self.get_total_minutes_asleep(row)
                total_minutes_in_bed = self.get_total_minutes_in_bed(row)
                if user_id not in users_data:
                    users_data[user_id] = dict()
                if date not in users_data[user_id]:
                    users_data[user_id][date] = [
                        total_minutes_asleep, total_minutes_in_bed]
        return users_data

    def append_to_file(self, write_file_path: str, users_data: list, column_names: str) -> None:
        with open(write_file_path) as csvfile:
            write_text = csvfile.readlines()

        with open(write_file_path, "w") as csvfile:
            for row in write_text:
                row = row.strip('\n')
                row_split = row.split(',')
                user_id = row_split[1]
                date = row_split[2]
                if (row_split[1] == "Id"):
                    row += column_names
                elif user_id in users_data and date in users_data[user_id]:
                    vals = users_data[user_id][date]
                    row += ','+str(vals[0])+','+str(vals[1])+'\n'
                else:
                    row += ','+str(0)+','+str(0)+'\n'
                csvfile.write(row)

    def revert_changes(self, current_file_path: str, base_file_path: str):
        with open(base_file_path) as f:
            write_text = f.readlines()

        with open(current_file_path, "w") as f:
            for row in write_text:
                f.write(row)

    @staticmethod
    def get_date(row: list) -> str:
        ans: str = ""
        for each in row[1]:
            if (each == ' '):
                break
            ans += each
        return ans

    @staticmethod
    def get_user_id(row: list) -> str:
        return row[0]

    @staticmethod
    def get_heartrate(row: list) -> int:
        return int(row[2])

    @staticmethod
    def get_total_minutes_asleep(row: list) -> int:
        return int(row[3])

    @staticmethod
    def get_total_minutes_in_bed(row: list) -> int:
        return int(row[4])


if __name__ == "__main__":
    cur_dir: str = os.path.dirname(__file__)
    csvhelper = CSVhelper()

    heartrate_file_path = cur_dir + heartrate_file
    sleep_file_path = cur_dir + sleep_file
    write_file_path = cur_dir + write_file
    base_file_path = cur_dir + base_file

    csvhelper.revert_changes(write_file_path, base_file_path)

    csvhelper.append_to_file(write_file_path, csvhelper.retrieve_heartrate_data(
        heartrate_file_path), ",MinHeartRate,MaxHeartRate\n")

    csvhelper.append_to_file(write_file_path, csvhelper.retrieve_sleep_data(
        sleep_file_path), ",TotalMinutesAsleep,TotalTimeInBed\n")
