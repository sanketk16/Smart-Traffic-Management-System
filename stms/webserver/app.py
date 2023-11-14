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


from flask import Flask, jsonify, send_from_directory
import os

app = Flask(__name__, static_folder='../frontend')

@app.route('/status', methods=['GET'])
def get_status():
    traffic_states = {}
    if os.path.exists("traffic_states.txt"):
        with open("traffic_states.txt", "r") as file:
            for line in file:
                parts = line.split(": ")
                if len(parts) == 2:
                    intersection, state = parts
                    traffic_states[intersection.strip()] = state.strip()
    else:
        traffic_states = {"error": "Traffic states file not found."}
    return jsonify(traffic_states)

@app.route('/')
def index():
    return send_from_directory(app.static_folder, 'index.html')

if __name__ == '__main__':
    app.run(debug=True)