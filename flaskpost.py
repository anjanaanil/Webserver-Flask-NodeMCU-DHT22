from flask import Flask, jsonify,render_template,request,redirect,url_for
#import requests
class DataStore():
    temperature=None
    humidity=None
data=DataStore()
#from flask import Flask
app = Flask(__name__)

@app.route("/",methods=['POST'])
def postJsonHandler():
    print(request.is_json)
    content=request.get_json()
    data.temperature=content['d']['temperature']
    data.humidity=content['d']['humidity']
    print(content['d']['temperature'])
    print(content['d']['humidity'])
    return 'Hello'

@app.route("/post")
def post():
    temperature=data.temperature
    humidity=data.humidity
    if temperature is None and humidity is None:
        temperature,humidity=20,30
    return render_template("sensor.html",temperature=temperature, humidity=humidity)


if __name__ == "__main__":
    app.debug=True
    app.run(host='0.0.0.0',port=8090)
