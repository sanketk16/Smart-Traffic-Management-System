# import numpy as np

# # Simulate historical traffic data for an intersection
# historical_traffic_data = np.random.randint(0, 100, size=100)

# def predict_traffic(historical_data, prediction_window):
#     weights = np.linspace(1, 0, num=len(historical_data))
#     weighted_avg = np.average(historical_data, weights=weights)
#     prediction = weighted_avg + np.random.normal(0, 10)
#     return max(0, prediction)

# # Predict traffic for the next interval
# next_interval_prediction = predict_traffic(historical_traffic_data, 1)
# print(f"Predicted traffic for the next interval: {next_interval_prediction}")

# import numpy as np

# # Simulate historical traffic data for an intersection
# historical_traffic_data = np.random.randint(0, 100, size=100)

# def predict_traffic(historical_data, prediction_window):
#     weights = np.linspace(1, 0, num=len(historical_data))
#     weighted_avg = np.average(historical_data, weights=weights)
#     prediction = weighted_avg + np.random.normal(0, 10)
#     return max(0, prediction)

# # Predict traffic for the next interval
# next_interval_prediction = predict_traffic(historical_traffic_data, 1)

# # Write prediction to a file
# with open("traffic_prediction.txt", "w") as file:
#     file.write(f"{next_interval_prediction}\n")

# print(f"Predicted traffic for the next interval: {next_interval_prediction}")

# import numpy as np
# import time

# # Function to generate simulated historical traffic data
# def generate_historical_data():
#     return np.random.randint(0, 100, size=100)

# def predict_traffic(historical_data):
#     weights = np.linspace(1, 0, num=len(historical_data))
#     weighted_avg = np.average(historical_data, weights=weights)
#     prediction = weighted_avg + np.random.normal(0, 10)
#     return max(0, prediction)

# def main():
#     while True:
#         historical_traffic_data = generate_historical_data()
#         next_interval_prediction = predict_traffic(historical_traffic_data)

#         # with open("traffic_prediction.txt", "w") as file:
#         with open("../webserver/traffic_prediction.txt", "w") as file:
#             file.write(f"{next_interval_prediction}\n")

#         print(f"Predicted traffic for the next interval: {next_interval_prediction}")

#         time.sleep(20)  # Wait for 20 seconds before the next prediction

# if __name__ == "__main__":
#     main()

# import numpy as np
# import pmdarima as pm
# import time

# # Function to generate simulated historical traffic data
# def generate_historical_data():
#     return np.random.randint(0, 100, size=100)

# def predict_traffic_arima(historical_data):
#     model = pm.auto_arima(historical_data, seasonal=False, error_action='ignore', suppress_warnings=True)
#     prediction = model.predict(n_periods=1)[0]
#     return max(0, prediction)

# def main():
#     while True:
#         historical_traffic_data = generate_historical_data()
#         next_interval_prediction = predict_traffic_arima(historical_traffic_data)

#         with open("../webserver/traffic_prediction.txt", "w") as file:
#             file.write(f"{next_interval_prediction}\n")

#         print(f"Predicted traffic for the next interval: {next_interval_prediction}")

#         time.sleep(20)  # Wait for 20 seconds before the next prediction

# if __name__ == "__main__":
#     main()

import numpy as np
import pmdarima as pm
import time
import logging
from datetime import datetime
import os

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# def generate_historical_data(size=1000):
#     # Generate more realistic data (you can replace this with actual historical data)
#     return np.random.randint(0, 100, size=size)

def generate_historical_data(size=1000):
    # Simulate more realistic data with peaks (e.g., rush hours) and troughs (e.g., night time)
    data = []
    for i in range(size):
        if i % 24 in [8, 9, 17, 18]:  # Simulate rush hours
            data.append(np.random.randint(60, 100))
        elif i % 24 in [0, 1, 2, 3]:  # Simulate late night
            data.append(np.random.randint(0, 30))
        else:
            data.append(np.random.randint(30, 60))
    return np.array(data)


def predict_traffic_arima(historical_data):
    try:
        model = pm.auto_arima(historical_data, seasonal=True, m=7, error_action='ignore', suppress_warnings=True)
        prediction = model.predict(n_periods=1)[0]
        return max(0, prediction)
    except Exception as e:
        logging.error(f"Error in model prediction: {e}")
        return 0

def main():
    while True:
        historical_traffic_data = generate_historical_data()
        next_interval_prediction = predict_traffic_arima(historical_traffic_data)

        # Dynamic file path handling
        file_path = os.path.join(os.path.dirname(__file__), "..", "webserver", "traffic_prediction.txt")

        try:
            with open(file_path, "w") as file:
                file.write(f"{next_interval_prediction}\n")
        except IOError as e:
            logging.error(f"File operation failed: {e}")

        logging.info(f"Predicted traffic for the next interval: {next_interval_prediction}")

        # Sleep time can be adjusted or made dynamic
        time.sleep(7)

if __name__ == "__main__":
    main()



