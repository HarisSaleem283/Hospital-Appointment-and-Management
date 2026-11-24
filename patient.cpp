#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct PatientNode
{
  int id;
  string name;
  int age;
  string gender;
  string phone;
  string disease;
  PatientNode *next;

  PatientNode(int i, string n, int a, string g, string p, string d)
  {
    id = i;
    name = n;
    age = a;
    gender = g;
    phone = p;
    disease = d;
    next = NULL;
  }
};

PatientNode *head = NULL;

// Check whether gender is Male or Female
int validGender(string gender)
{
  for (int i = 0; i < gender.length(); i++)
  {
    gender[i] = tolower(gender[i]);
  }

  if (gender == "male" || gender == "female")
    return 1;

  return 0;
}

// Add a patient at the end of the linked list
int addPatient(int id, string name, int age, string gender,
               string phone, string disease)
{
  if (id <= 0 || name.empty() || age < 1 || age > 120 ||
      !validGender(gender) || phone.empty() || disease.empty())
  {
    return 0;
  }

  PatientNode *temp = head;

  while (temp != NULL)
  {
    if (temp->id == id)
      return 0;

    temp = temp->next;
  }

  PatientNode *newNode =
      new PatientNode(id, name, age, gender, phone, disease);

  if (head == NULL)
  {
    head = newNode;
  }
  else
  {
    temp = head;

    while (temp->next != NULL)
      temp = temp->next;

    temp->next = newNode;
  }

  return 1;
}

// Check whether a patient ID exists
int patientExists(int id)
{
  PatientNode *temp = head;

  while (temp != NULL)
  {
    if (temp->id == id)
      return 1;

    temp = temp->next;
  }

  return 0;
}

// Update patient details
int updatePatient(int id, string name, int age, string gender,
                  string phone, string disease)
{
  if (name.empty() || age < 1 || age > 120 ||
      !validGender(gender) || phone.empty() || disease.empty())
  {
    return 0;
  }

  PatientNode *temp = head;

  while (temp != NULL)
  {
    if (temp->id == id)
    {
      temp->name = name;
      temp->age = age;
      temp->gender = gender;
      temp->phone = phone;
      temp->disease = disease;

      return 1;
    }

    temp = temp->next;
  }

  return 0;
}

// Delete a patient
int deletePatient(int id)
{
  if (head == NULL)
    return 0;

  PatientNode *temp = head;
  PatientNode *previous = NULL;

  while (temp != NULL && temp->id != id)
  {
    previous = temp;
    temp = temp->next;
  }

  if (temp == NULL)
    return 0;

  if (previous == NULL)
    head = temp->next;
  else
    previous->next = temp->next;

  delete temp;
  return 1;
}

// Display all patients
void displayPatients()
{
  if (head == NULL)
  {
    cout << "\nNo patients registered.\n";
    return;
  }

  PatientNode *temp = head;

  cout << "\n----------- PATIENT RECORDS -----------\n";

  while (temp != NULL)
  {
    cout << "\nPatient ID: " << temp->id;
    cout << "\nName: " << temp->name;
    cout << "\nAge: " << temp->age;
    cout << "\nGender: " << temp->gender;
    cout << "\nPhone: " << temp->phone;
    cout << "\nDisease: " << temp->disease << "\n";

    temp = temp->next;
  }
}

// Return the number of patients
int getPatientCount()
{
  int count = 0;
  PatientNode *temp = head;

  while (temp != NULL)
  {
    count++;
    temp = temp->next;
  }

  return count;
}

// Get a patient by its position for file saving
int getPatientAt(int position, int &id, string &name, int &age,
                 string &gender, string &phone, string &disease)
{
  PatientNode *temp = head;
  int index = 0;

  while (temp != NULL)
  {
    if (index == position)
    {
      id = temp->id;
      name = temp->name;
      age = temp->age;
      gender = temp->gender;
      phone = temp->phone;
      disease = temp->disease;

      return 1;
    }

    index++;
    temp = temp->next;
  }

  return 0;
}

// Clear the list before loading saved records
void clearPatients()
{
  PatientNode *temp = head;

  while (temp != NULL)
  {
    PatientNode *nextNode = temp->next;
    delete temp;
    temp = nextNode;
  }

  head = NULL;
}

// Free linked-list memory when the program finishes
void cleanupPatients()
{
  clearPatients();
}
