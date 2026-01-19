#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// --- DATA STRUCTURE ---
struct User {
    string username;
    string password;
    float weight;
    float height;
    int calorieGoal;
    int currentCalories = 0;
    int waterIntake = 0;
};

// --- ROBUST INPUT VALIDATION FUNCTIONS ---
int getInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input. Please enter a positive whole number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

float getFloat(string prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input. Please enter a positive decimal number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// --- APP INFORMATION ---
void showAbout() {
    cout << "\n==============================================" << endl;
    cout << "          WELCOME TO FITTRACK v1.0            " << endl;
    cout << "==============================================" << endl;
    cout << "Your personal health companion to monitor:" << endl;
    cout << "1. Calorie Intake   2. Exercise Burn" << endl;
    cout << "3. Water Tracking   4. BMI Analysis" << endl;
    cout << "----------------------------------------------" << endl;
}

// WRITTEN BY MESUD

// WRITTEN BY KIDUS

void logExercise(User &u) {
    string activities[] = {"Running", "Walking", "Cycling", "Swimming", "Weightlifting"};
    float burnRate[] = {11.4, 4.0, 8.0, 10.0, 5.0}; // kcal per minute

    cout << "\n--- EXERCISE DATABASE ---\n";
    for(int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << left << setw(15) << activities[i] << "(" << burnRate[i] << " kcal/min)" << endl;
    }
    cout << "6. Custom Entry" << endl;

    int choice = getInt("Select activity (1-6): ");
    if (choice >= 1 && choice <= 5) {
        int mins = getInt("Duration in minutes: ");
        int burned = (int)(burnRate[choice - 1] * mins);
        u.currentCalories -= burned;
        cout << "🔥 You burned " << burned << " calories!\n";
    } else if (choice == 6) {
        u.currentCalories -= getInt("Enter calories burned: ");
    }
}
// WRITTEN BY MANASSEH SAMUEL
// --- REPORT & BMI LOGIC ---
void showReport(User u) {
    float heightM = u.height / 100.0;
    float bmi = u.weight / (heightM * heightM);

    cout << "\n==============================================" << endl;
    cout << "            DAILY PROGRESS REPORT             " << endl;
    cout << "==============================================" << endl;
    cout << "User: " << u.username << " | BMI: " << fixed << setprecision(1) << bmi << endl;
    cout << "Status: ";
    if (bmi < 18.5) cout << "Underweight";
    else if (bmi < 24.9) cout << "Normal Weight";
    else cout << "Overweight";
    
    cout << "\n----------------------------------------------" << endl;
    cout << "Calories: " << u.currentCalories << " / " << u.calorieGoal << " kcal" << endl;
    cout << "Water Intake: " << u.waterIntake << " / 8 glasses" << endl;
    
    int remaining = u.calorieGoal - u.currentCalories;
    if (remaining >= 0) cout << "Result: You can eat " << remaining << " more calories today." << endl;
    else cout << "Result: You are OVER your goal by " << abs(remaining) << " calories!" << endl;
    cout << "==============================================\n" << endl;
}

// --- FILE DATABASE SYSTEM ---
void saveToFile(User db[], int count) {
    ofstream f("data.txt");
    for (int i = 0; i < count; i++) {
        f << db[i].username << " " << db[i].password << " " << db[i].weight << " " 
          << db[i].height << " " << db[i].calorieGoal << " " 
          << db[i].currentCalories << " " << db[i].waterIntake << endl;
    }
    f.close();
}

void loadFromFile(User db[], int &count) {
    ifstream f("data.txt");
    if (!f) return;
    count = 0;
    while (f >> db[count].username >> db[count].password >> db[count].weight 
             >> db[count].height >> db[count].calorieGoal 
             >> db[count].currentCalories >> db[count].waterIntake) {
        count++;
    }
    f.close();
}

// --- MAIN CONTROL CENTER ---
int main() {
    User database[100];
    int userCount = 0, currentUserIndex = -1;
    loadFromFile(database, userCount);

    showAbout();

    cout << "1. Login\n2. Sign Up\n3. Exit\n";
    int mode = getInt("Choice: ");

    if (mode == 3) return 0;

    if (mode == 2) {
        if (userCount >= 100) {
            cout << "Database full!\n";
            return 0;
        }
        cout << "Set Username (no spaces): "; cin >> database[userCount].username;
        cout << "Set Password: "; cin >> database[userCount].password;
        database[userCount].weight = getFloat("Your Weight (kg): ");
        database[userCount].height = getFloat("Your Height (cm): ");
        database[userCount].calorieGoal = getInt("Daily Calorie Goal: ");
        currentUserIndex = userCount;
        userCount++;
    } else {
        string u, p;
        cout << "Username: "; cin >> u;
        cout << "Password: "; cin >> p;
        for (int i = 0; i < userCount; i++) {
            if (database[i].username == u && database[i].password == p) {
                currentUserIndex = i;
                break;
            }
        }
    }

    if (currentUserIndex != -1) {
        int choice;
        do {
            cout << "\n--- MAIN MENU ---";
            cout << "\n1. Log Food\n2. Log Exercise\n3. Log 1 Glass Water\n4. View Report\n5. Save & Exit\n";
            choice = getInt("Selection: ");

            if (choice == 1) logFood(database[currentUserIndex]);
            else if (choice == 2) logExercise(database[currentUserIndex]);
            else if (choice == 3) {
                database[currentUserIndex].waterIntake++;
                cout << "💧 Water logged! (" << database[currentUserIndex].waterIntake << "/8)\n";
            }
            else if (choice == 4) showReport(database[currentUserIndex]);
        } while (choice != 5);

        saveToFile(database, userCount);
        cout << "\nData saved successfully. Stay healthy!\n";
    } else {
        cout << "\n❌ Access Denied: Incorrect username or password.\n";
    }

    system("pause");
    return 0;
}
