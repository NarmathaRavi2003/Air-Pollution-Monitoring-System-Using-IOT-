import requests
import smtplib
from email.message import EmailMessage
import ssl

# Function to get the latest air quality data from ThingSpeak
def get_latest_air_quality():
    url = 'https://api.thingspeak.com/channels/2543851/feeds.json?results=1'
    response = requests.get(url)
    data = response.json()
    print("API Response:", data)  # Debug statement
    if 'feeds' in data and len(data['feeds']) > 0:
        try:
            return float(data['feeds'][0]['field3'])
        except ValueError as e:
            print(f"Error parsing air quality data: {e}")
            return None
    return None

# Function to read user emails from a file
def get_user_emails():
    user_emails = []
    try:
        with open('user_credentials.txt', 'r') as file:
            lines = file.readlines()
            for line in lines:
                username, _ = line.strip().split(',')
                user_emails.append(username)
    except FileNotFoundError:
        print("user_credentials.txt file not found")
    return user_emails

# Function to send an email alert
def send_email_alert(to_email, air_quality):
    from_email = 'gmailaccount'
    email_password = 'password(16) after 2 step verification'
    smtp_server = 'smtp.gmail.com'
    smtp_port = 465

    subject = 'Air Quality Alert'
    body = f'The current air quality is {air_quality}, which is above the safe threshold.'

    em = EmailMessage()
    em['From'] = from_email
    em['To'] = to_email
    em['Subject'] = subject
    em.set_content(body)

    context = ssl.create_default_context()

    try:
        print(f"Connecting to SMTP server: {smtp_server}")  # Debug statement
        with smtplib.SMTP_SSL(smtp_server, smtp_port, context=context) as smtp:
            smtp.login(from_email, email_password)
            print("Sending email...")  # Debug statement
            smtp.sendmail(from_email, to_email, em.as_string())
            print(f"Email sent to {to_email}")  # Debug statement
    except Exception as e:
        print(f"Failed to send email: {e}")

# Main function to check air quality and send alerts
def main():
    air_quality = get_latest_air_quality()
    if air_quality is None:
        print("Failed to retrieve air quality data")
        return

    if air_quality > 50:  # Lowered the threshold for testing
        user_emails = get_user_emails()
        for email in user_emails:
            send_email_alert(email, air_quality)

if __name__ == "__main__":
    main()
