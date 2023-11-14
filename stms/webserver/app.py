# from flask import Flask, jsonify, send_from_directory
# from flask_socketio import SocketIO
# import os

# app = Flask(__name__, static_folder='../frontend')
# app.config['SECRET_KEY'] = 'secret!'
# socketio = SocketIO(app)

# @app.route('/status', methods=['GET'])
# def get_status():
#     traffic_states = {}
#     if os.path.exists("traffic_states.txt"):
#         with open("traffic_states.txt", "r") as file:
#             for line in file:
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     intersection, state = parts
#                     traffic_states[intersection.strip()] = state.strip()
#     else:
#         traffic_states = {"error": "Traffic states file not found."}
#     return jsonify(traffic_states)

# @app.route('/')
# def index():
#     return send_from_directory(app.static_folder, 'index.html')

# @socketio.on('connect')
# def handle_connect():
#     print('Client connected')

# @socketio.on('disconnect')
# def handle_disconnect():
#     print('Client disconnected')

# # Function to emit traffic light status updates
# def emit_traffic_status_update():
#     traffic_states = {}  # Get the latest traffic states
#     # Populate traffic_states with current traffic light information
#     # and time remaining for each state
#     socketio.emit('traffic_update', traffic_states)

# if __name__ == '__main__':
#     app.run(debug=True)
#     # socketio.run(app, debug=True)

# # from flask import Flask, send_from_directory
# # from flask_socketio import SocketIO
# # import os
# # import threading
# # import time

# # app = Flask(__name__, static_folder='../frontend')
# # app.config['SECRET_KEY'] = 'your_secret_key'
# # socketio = SocketIO(app)

# # def read_and_emit_traffic_states():
# #     while True:
# #         traffic_states = {}
# #         if os.path.exists("traffic_states.txt"):
# #             with open("traffic_states.txt", "r") as file:
# #                 for line in file:
# #                     parts = line.split(": ")
# #                     if len(parts) == 2:
# #                         intersection, state_info = parts
# #                         traffic_states[intersection.strip()] = state_info.strip()
# #         socketio.emit('traffic_update', traffic_states)
# #         time.sleep(1)  # Poll every second

# # @app.route('/')
# # def index():
# #     return send_from_directory(app.static_folder, 'index.html')

# # @socketio.on('connect')
# # def handle_connect():
# #     print('Client connected')

# # @socketio.on('disconnect')
# # def handle_disconnect():
# #     print('Client disconnected')

# # if __name__ == '__main__':
# #     threading.Thread(target=read_and_emit_traffic_states, daemon=True).start()
# #     socketio.run(app, debug=False)


# from flask import Flask, jsonify, send_from_directory
# import os

# app = Flask(__name__, static_folder='../frontend')

# @app.route('/status', methods=['GET'])
# def get_status():
#     traffic_states = {}
#     if os.path.exists("traffic_states.txt"):
#         with open("traffic_states.txt", "r") as file:
#             for line in file:
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     intersection, state = parts
#                     traffic_states[intersection.strip()] = state.strip()
#     else:
#         traffic_states = {"error": "Traffic states file not found."}
#     return jsonify(traffic_states)

# @app.route('/')
# def index():
#     return send_from_directory(app.static_folder, 'index.html')

# if __name__ == '__main__':
#     app.run(debug=True)

# from flask import Flask, jsonify, send_from_directory
# import os

# app = Flask(__name__, static_folder='../frontend')

# @app.route('/status', methods=['GET'])
# def get_status():
#     traffic_states = {}
#     if os.path.exists("traffic_states.txt"):
#         with open("traffic_states.txt", "r") as file:
#             for line in file:
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     intersection, state = parts
#                     traffic_states[intersection.strip()] = state.strip()
#     else:
#         traffic_states = {"error": "Traffic states file not found."}
#     return jsonify(traffic_states)

# @app.route('/')
# def index():
#     return send_from_directory(app.static_folder, 'index.html')

# if __name__ == '__main__':
#     app.run(debug=True)

from flask import Flask, jsonify, send_from_directory, make_response
import os

app = Flask(__name__, static_folder='../frontend')

# @app.route('/status', methods=['GET'])
# def get_status():
#     traffic_states = {}
#     if os.path.exists("traffic_states.txt"):
#         with open("traffic_states.txt", "r") as file:
#             for line in file:
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     intersection, state = parts
#                     traffic_states[intersection.strip()] = state.strip()
#     else:
#         traffic_states = {"error": "Traffic states file not found."}
#     return jsonify(traffic_states)

# @app.route('/status', methods=['GET'])
# def get_status():
#     traffic_states = {}
#     if os.path.exists("traffic_states.txt"):
#         with open("traffic_states.txt", "r") as file:
#             for line in file:
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     intersection_info, state_info = parts
#                     state, remaining = state_info.split(" (Remaining Time: ")
#                     remaining_time = remaining.split(" ")[0]
#                     traffic_states[intersection_info.strip()] = {"state": state.strip(), "remaining_time": int(remaining_time)}
#     else:
#         traffic_states = {"error": "Traffic states file not found."}
#     return jsonify(traffic_states)
# @app.route('/status', methods=['GET'])
# def get_status():
#     print("Accessing /status endpoint")  # Debug print
#     traffic_states = {}
#     if os.path.exists("traffic_states.txt"):
#         with open("traffic_states.txt", "r") as file:
#             for line in file:
#                 print(f"Line from file: {line}")  # Debug print
#                 parts = line.split(": ")
#                 if len(parts) == 2:
#                     intersection_info, state_info = parts
#                     state, remaining = state_info.split(" (Remaining Time: ")
#                     remaining_time = remaining.split(" ")[0]
#                     traffic_states[intersection_info.strip()] = {"state": state.strip(), "remaining_time": int(remaining_time)}
#     else:
#         print("File not found.")  # Debug print
#         traffic_states = {"error": "Traffic states file not found."}

#     print(traffic_states)  # Debug print
#     return jsonify(traffic_states)

@app.route('/status', methods=['GET'])
def get_status():
    print("Accessing /status endpoint")
    traffic_states = {}
    if os.path.exists("traffic_states.txt"):
        with open("traffic_states.txt", "r") as file:
            for line in file:
                print(f"Line from file: {line}")
                try:
                    intersection, state_with_remaining = line.strip().split(": ", 1)
                    state, remaining = state_with_remaining.split(" (Remaining Time: ")
                    remaining_time = remaining.split(" seconds)")[0]
                    # Adjust the intersection number if needed
                    traffic_states[intersection] = {"state": state, "remaining_time": int(remaining_time)}
                except ValueError as e:
                    print(f"Error processing line: {line}, Error: {e}")
    else:
        print("File not found.")
        traffic_states = {"error": "Traffic states file not found."}

    print(traffic_states)
    return jsonify(traffic_states)





@app.route('/prediction', methods=['GET'])
def get_prediction():
    if os.path.exists("traffic_prediction.txt"):
        with open("traffic_prediction.txt", "r") as file:
            prediction_value = file.readline().strip()
            return jsonify({"value": prediction_value})
    else:
        return jsonify({"error": "Traffic prediction file not found."})

@app.route('/')
def index():
    return send_from_directory(app.static_folder, 'index.html')

if __name__ == '__main__':
    app.run(debug=True)

