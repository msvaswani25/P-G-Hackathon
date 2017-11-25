from flask import Flask, jsonify,  request,render_template
from flask import abort
import json
import datetime
import os
from random import randint


app = Flask(__name__)


@app.route('/index', methods=['GET'])
def hello_world():
    return "Hello World"


@app.route('/get/user', methods=['GET'])
def get_score():
    users=[]
    users_data=os.listdir("user_data")
    for user_file in users_data:
        users.append(json.load(open('user_data/'+user_file)))
    print (users)    
    user_id = int(request.values.get('inputId', 0))
    print (type(user_id))
    user = [user for user in users if user['id'] == user_id]
    if len(user) == 0:
        abort(404)
    return jsonify(user[0])


@app.route('/update/data', methods=['PUT'])
def update_data():
    users=[]
    users_data=os.listdir("user_data")
    for user_file in users_data:
        print(user_file)
        print(type(user_file))
        print(json.load(open('user_data/'+user_file)))
        users.append(json.load(open('user_data/'+user_file)))   
    print ()
    print (users)    
    id=request.values.get('user_id', 0)
    user_id = int(id)    
    data = (request.values.get('data', '')).split(',')
    user = [user for user in users if user['id'] == user_id]
    datetime.datetime.today().strftime('%Y-%m-%d')
    d = str(datetime.datetime.now().date())
    
    if len(user) == 0:
        abort(404)
    user[0]['scores'].append({"date":d,"score":calculateScore(data)})
    user[0]['totalScore']=calculateTotalScore(user[0])
    with open('user_data/'+id+".json", 'w') as outfile:
                json.dump(user[0], outfile)
    
    return jsonify(user[0])

def calculateScore(data):
    
    return randint(70, 100)

def calculateTotalScore(user):
    sum=0.0
    for score in user['scores']:
        sum+=score['score']
    return sum/len(user['scores'])

@app.route('/add/user', methods=['POST'])
def add_user():
    id=json.load(open('user_data/id.json'))['id']
    user_id = int(id)
    user_name = request.values.get('inputName', '')
    user_age = int(request.values.get('inputAge', 0))
    user=dict()
    user['id']=int(user_id)
    user['name']=user_name
    user['age']=user_age
    user['totalScore']=0
    user['scores']=[]   
    with open('user_data/'+str(id)+".json", 'w') as outfile:
                json.dump(user, outfile)
    with open('user_data/id.json', 'w') as outfile:
                json.dump({'id':id+1}, outfile)            
    return jsonify(user)            
             
                
@app.route("/addChild")
def addChild():
    return render_template('add_child.html')
@app.route("/")
def main():
    return render_template('index.html')
@app.route("/insights")
def insights():
    return render_template('all_insights.html')

if __name__ == '__main__':
    app.run(host= '0.0.0.0', port=5000)
