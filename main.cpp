#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ================= FUNCTION DECLARATIONS =================
// g++ -std=c++17 main.cpp patient.cpp appointment.cpp file.cpp 
// -o hospital.exe
//.\hospital.exe
// Patient functions
int addPatient(int id, string name, int age, string gender,string phone, string disease);

int updatePatient(int id, string name, int age, string gender,
string phone, string disease);

int deletePatient(int id);
int patientExists(int id);

void displayPatients();
void cleanupPatients();

// Appointment functions
int addAppointment(int aID, int pID, string doctor,
string date, string time);

int updateAppointment(int id, string doctor,
string date, string time);

int processNextAppointment();
int cancelAppointment(int id);
int completeAppointment(int id);

void displayAppointments();
void displayQueue();
void bubbleSort();
int linearSearch(int id);
void clearAppointments();

// File functions
void saveRecords();
void loadRecords();

// ================= PATIENT MENU =================
int validGender(string gender);

void patientMenu()
{
  int choice;

  do
  {
    cout << "\n========== PATIENT MENU ==========\n";
    cout << "1. Add Patient\n";
    cout << "2. Update Patient\n";
    cout << "3. Delete Patient\n";
    cout << "4. Display All Patients\n";
    cout << "0. Back to Main Menu\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
      int id, age;
      string name, gender, phone, disease;

      cout << "\nEnter Patient ID: ";
      cin >> id;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Enter Name: ";
      getline(cin, name);

cout << "Enter Age: ";
cin >> age;

cin.ignore(numeric_limits<streamsize>::max(), '\n');
      do
{
    cout << "Enter Gender (Male/Female): ";
    getline(cin,gender);

    if (!validGender(gender))
    {
  cout << "Invalid gender! Enter Male or Female.\n";
    }

} while (!validGender(gender));
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Enter Phone: ";
getline(cin, phone);

cout << "Enter Disease: ";
getline(cin, disease);
if (addPatient(id, name, age, gender, phone, disease))
cout << "\nPatient added successfully.\n";
else
cout << "\nUnable to add patient. Check the details or ID.\n";
    }
else if (choice == 2)
    {
 int id, age;
string name, gender, phone, disease;

cout << "\nEnter Patient ID to update: ";
cin >> id;

cin.ignore(numeric_limits<streamsize>::max(), '\n');

cout << "Enter New Name: ";
getline(cin, name);

cout << "Enter New Age: ";
cin >> age;

cin.ignore(numeric_limits<streamsize>::max(), '\n');

cout << "Enter New Gender: ";
getline(cin, gender);

cout << "Enter New Phone: ";
getline(cin, phone);

cout << "Enter New Disease: ";
      getline(cin, disease);

      if (updatePatient(id, name, age, gender, phone, disease))
        cout << "\nPatient updated successfully.\n";
      else
        cout << "\nPatient not found or invalid details.\n";
    }

    else if (choice == 3)
    {
      int id;

      cout << "\nEnter Patient ID to delete: ";
      cin >> id;

      if (deletePatient(id))
        cout << "\nPatient deleted successfully.\n";
      else
        cout << "\nPatient not found.\n";
    }

    else if (choice == 4)
    {
      displayPatients();
    }

    else if (choice != 0)
    {
      cout << "\nInvalid choice.\n";
    }

  } while (choice != 0);
}

// ================= APPOINTMENT MENU =================

void appointmentMenu()
{
  int choice;

  do
  {
    cout << "\n========== APPOINTMENT MENU ==========\n";
    cout << "1. Add Appointment\n";
    cout << "2. Update Appointment\n";
    cout << "3. Process Next Appointment\n";
    cout << "4. Cancel Appointment\n";
    cout << "5. Complete Appointment\n";
    cout << "6. Display All Appointments\n";
    cout << "7. Display Pending Queue\n";
    cout << "8. Sort Appointments by ID\n";
    cout << "9. Search Appointment\n";
    cout << "0. Back to Main Menu\n";

    cout << "\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
      int aID, pID;
      string doctor, date, time;

      cout << "\nEnter Appointment ID: ";
      cin >> aID;

      cout << "Enter Patient ID: ";
      cin >> pID;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Enter Doctor Name: ";
      getline(cin, doctor);

      cout << "Enter Date: ";
      getline(cin, date);

      cout << "Enter Time: ";
      getline(cin, time);
if (addAppointment(aID, pID, doctor, date, time))
{
cout << "\nAppointment added successfully.\n";
saveRecords();
}


else
  cout << "\nUnable to add appointment. Check patient ID, appointment ID or doctor availability.\n";
    }

else if (choice == 2)
    {
int id;
      string doctor, date, time;

      cout << "\nEnter Appointment ID: ";
      cin >> id;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "Enter New Doctor Name: ";
      getline(cin, doctor);

      cout << "Enter New Date: ";
      getline(cin, date);

      cout << "Enter New Time: ";
      getline(cin, time);

      if (updateAppointment(id, doctor, date, time))
        cout << "\nAppointment updated successfully.\n";
      else
        cout << "\nUnable to update appointment.\n";
    }

    else if (choice == 3)
    {
      if (processNextAppointment())
        cout << "\nNext appointment has been scheduled.\n";
      else
        cout << "\nNo pending appointment available.\n";
    }

    else if (choice == 4)
    {
      int id;

      cout << "\nEnter Appointment ID to cancel: ";
      cin >> id;

      if (cancelAppointment(id))
        cout << "\nAppointment cancelled successfully.\n";
      else
        cout << "\nUnable to cancel appointment.\n";
    }

    else if (choice == 5)
    {
      int id;

      cout << "\nEnter Appointment ID to complete: ";
      cin >> id;

      if (completeAppointment(id))
        cout << "\nAppointment completed successfully.\n";
      else
        cout << "\nUnable to complete appointment. It must be scheduled first.\n";
    }

    else if (choice == 6)
    {
      displayAppointments();
    }

    else if (choice == 7)
    {
      displayQueue();
    }

    else if (choice == 8)
    {
      bubbleSort();

      cout << "\nAppointments sorted by ID.\n";
      displayAppointments();
    }

    else if (choice == 9)
    {
      int id;

      cout << "\nEnter Appointment ID to search: ";
      cin >> id;

      int position = linearSearch(id);

      if (position != -1)
      {
        cout << "\nAppointment found at position: "
             << position + 1 << endl;
      }
      else
      {
        cout << "\nAppointment not found.\n";
      }
    }

    else if (choice != 0)
    {
      cout << "\nInvalid choice.\n";
    }

  } while (choice != 0);
}

// ================= MAIN FUNCTION =================

int main()
{
  int choice;

  // Load saved records when program starts
  loadRecords();

  do
  {
    cout << "\n====================================\n";
    cout << "       HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "====================================\n";

    cout << "1. Patient Management\n";
    cout << "2. Appointment Management\n";
    cout << "0. Save and Exit\n";

    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
      patientMenu();
    }

    else if (choice == 2)
    {
      appointmentMenu();
    }

    else if (choice == 0)
    {
      saveRecords();

      cout << "\nThank you for using Hospital Management System.\n";

      clearAppointments();
      cleanupPatients();
    }

    else
    {
      cout << "\nInvalid choice. Try again.\n";
    }

  } while (choice != 0);

  return 0;
}
