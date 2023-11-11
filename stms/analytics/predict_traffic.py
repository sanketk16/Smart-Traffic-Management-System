import numpy as np

# Simulate historical traffic data for an intersection
historical_traffic_data = np.random.randint(0, 100, size=100)

def predict_traffic(historical_data, prediction_window):
    weights = np.linspace(1, 0, num=len(historical_data))
    weighted_avg = np.average(historical_data, weights=weights)
    prediction = weighted_avg + np.random.normal(0, 10)
    return max(0, prediction)

# Predict traffic for the next interval
next_interval_prediction = predict_traffic(historical_traffic_data, 1)
print(f"Predicted traffic for the next interval: {next_interval_prediction}")