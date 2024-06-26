from flask import Flask, render_template, request, redirect
import hashlib
import re

def username_regex(username):
    username_regex = r"[a-zA-Z0-9_\-\.]{6,15}"
    match_regex = re.search(username_regex, username)
    return bool(match_regex)

def password_regex(password):
    password_regex = r"^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@?#$%^&*+=]).{8,}$"
    match_regex = re.search(password_regex, password)
    return bool(match_regex)

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def home():
    return render_template('index.html')

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    if request.method == 'POST':
        # Get the form data
        username = request.form['username']
        password = request.form['password']
        confirm_password = request.form['confirm-password']
        if username_regex(username) and password_regex(password):
            if confirm_password == password:
                with open('user_credentials.txt', 'a') as user_data:
                    hashed_password = hashlib.sha256(password.encode()).hexdigest()
                    user_data.write(f'{username},{hashed_password}' + "\n")
                return render_template('index.html')  # Redirect to the main page after signup
            else:
                return "Passwords don't match!"
        elif username_regex(username) and not password_regex(password):
            return "Password should be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, one digit, and one special character."
        elif not username_regex(username) and password_regex(password):
            return "Username can be alphanumeric and should be 6 to 15 characters long. It can contain characters '_', '-' and '.'."
        else:
            return "Invalid username and password format."
    else:
        return render_template('signup.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Get the form data
        entered_username = request.form['username']
        entered_password = request.form['password']

        hashed_entered_password = hashlib.sha256(entered_password.encode()).hexdigest()

        with open('user_credentials.txt', 'r') as user_data:
            user_credentials = user_data.readlines()

        for i in user_credentials:
            lst = i.split(',')
            if lst[0] == entered_username and lst[1].strip() == hashed_entered_password:
                return render_template('index.html')
            elif lst[0] != entered_username and lst[1].strip() == hashed_entered_password:
                return 'Incorrect username!'
            elif lst[0] == entered_username and lst[1].strip() != hashed_entered_password:
                return 'Incorrect password!'
        return "Looks like you're a new user, please signup first!"
    else:
        return render_template('login.html')

if __name__ == '__main__':
    app.run(debug=True)
