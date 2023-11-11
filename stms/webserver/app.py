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