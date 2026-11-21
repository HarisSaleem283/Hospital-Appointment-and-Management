
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// Functions from patient.cpp
int getPatientCount();

int getPatientAt(int position, int &id, string &name, int &age,
                 string &gender, string &phone, string &disease);

int addPatient(int id, string name, int age, string gender,
               string phone, string disease);

void clearPatients();

// Functions from appointment.cpp
int getAppointmentCount();

int getAppointmentAt(int position, int &appointmentID, int &patientID,
                     string &doctor, string &date, string &time,
                     string &status);

int loadAppointment(int aID, int pID, string doctor,
                    string date, string time, string status);

void clearAppointments();

// ================= SAVE RECORDS =================

void saveRecords()
{
  ofstream file("hospital_records.txt");

  if (!file)
  {
    cout << "\nError opening file.\n";
    return;
  }

  // Save patients
  int patientCount = getPatientCount();

  file << patientCount << endl;

  for (int i = 0; i < patientCount; i++)
  {
    int id, age;
    string name, gender, phone, disease;

    if (getPatientAt(i, id, name, age, gender, phone, disease))
    {
      file << id << " "
           << age << " "
           << quoted(name) << " "
           << quoted(gender) << " "
           << quoted(phone) << " "
           << quoted(disease) << endl;
    }
  }

  // Save appointments
  int appointmentCount = getAppointmentCount();

  file << appointmentCount << endl;

  for (int i = 0; i < appointmentCount; i++)
  {
    int appointmentID, patientID;
    string doctor, date, time, status;

    if (getAppointmentAt(i, appointmentID, patientID,
                         doctor, date, time, status))
    {
      file << appointmentID << " "
           << patientID << " "
           << quoted(doctor) << " "
           << quoted(date) << " "
           << quoted(time) << " "
           << quoted(status) << endl;
    }
  }

  file.close();

  if (!file)
  {
    cout << "\nError while saving records.\n";
    return;
  }

  cout << "\nPatient and appointment records saved successfully.\n";
}

// ================= LOAD RECORDS =================

void loadRecords()
{
  ifstream file("hospital_records.txt");

  if (!file)
  {
    cout << "\nNo saved records found. Starting a new system.\n";
    return;
  }

  // Clear existing lists before loading
  clearAppointments();
  clearPatients();

  int patientCount;

  if (!(file >> patientCount) || patientCount < 0)
  {
    cout << "\nInvalid patient records file.\n";
    return;
  }

  // Load patients first
  for (int i = 0; i < patientCount; i++)
  {
    int id, age;
    string name, gender, phone, disease;

    if (!(file >> id >> age >> quoted(name) >> quoted(gender) >> quoted(phone) >> quoted(disease)))
    {
      cout << "\nError reading patient records.\n";
      return;
    }

    if (!addPatient(id, name, age, gender, phone, disease))
    {
      cout << "\nWarning: A patient record could not be loaded.\n";
    }
  }

  int appointmentCount;

  if (!(file >> appointmentCount) || appointmentCount < 0)
  {
    cout << "\nInvalid appointment records section.\n";
    return;
  }

  // Load appointments after patients
  for (int i = 0; i < appointmentCount; i++)
  {
    int appointmentID, patientID;
    string doctor, date, time, status;

    if (!(file >> appointmentID >> patientID >> quoted(doctor) >> quoted(date) >> quoted(time) >> quoted(status)))
    {
      cout << "\nError reading appointment records.\n";
      return;
    }

    if (!loadAppointment(appointmentID, patientID,
                         doctor, date, time, status))
    {
      cout << "\nWarning: An appointment could not be loaded.\n";
    }
  }

  file.close();

  cout << "\nSaved records loaded successfully.\n";
}
