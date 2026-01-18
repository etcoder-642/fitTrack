# fitTrack
FitTrack Console is a simple, user-friendly C++ application designed to help people manage their fitness.

## Project Proposal: FitTrack Console v1.0
1. Executive Summary
FitTrack Console is a simple, user-friendly C++ application designed to help people manage their fitness. The app allows users to create an account, calculate their body metrics (like BMI), and log their daily food, exercise, and water intake. Unlike basic classroom projects, this app uses File Persistence, meaning it saves all user data to a text file so that progress is not lost when the computer is turned off.

2. Project Purpose
Many people want to track their fitness but find mobile apps too distracting or complex. FitTrack provides a "back-to-basics" tool that focuses on pure data.

### The Goal: 
To help users understand the balance between calories eaten and calories burned.

### The Problem solved: 
Most beginner C++ programs "forget" everything when they close. FitTrack solves this by saving data to a local .txt file.

3. Detailed Features (What the app does)
#### A. Account & Security
Sign-up/Login: Users create a username and password.

Memory: The app searches a file to find the user’s saved data.

Profile: Stores the user’s height, weight, age, and gender.

### B. Health Tools (The Math)
BMI Calculator: Tells the user if they are Underweight, Normal, Overweight, or Obese based on height/weight.

BMR & Daily Goal: The app calculates the user's Basal Metabolic Rate (calories burned at rest) and suggests a daily calorie target.

### C. Intake & Activity Logs
Food Logger: Users choose from a list (e.g., Rice, Meat, Vegetables). The app adds these calories to the daily total.

Water Tracker: A simple way to log glasses of water to reach a daily goal of 8 glasses.

Exercise Logger: Users pick an activity (e.g., Running, Walking) and enter the time spent. The app calculates calories burned based on the duration.

#### D. Progress Reports
Daily Summary: Displays a "Dashboard" showing:

Total Calories In vs. Out.

Net Calories (Remaining balance).

Water Goal progress bar.

4. Technical Components
The project is built using these core C++ building blocks:

Structs: To group user data (Username, Weight, Calories) into one package.

File I/O (fstream): To "Write" data to a file when saving and "Read" data when logging in.

Switch-Case Menus: To create an easy-to-navigate menu system.

Functions: To keep the code organized so different team members can work on different parts.