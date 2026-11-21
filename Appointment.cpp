
#include <iostream>
#include <string>
using namespace std;

// Function from patient.cpp
int patientExists(int id);

// Appointment node
struct Node
{
  int appointmentID;
  int patientID;
  string doctor;
  string date;
  string time;
  string status;

  Node *next;

  Node(int a, int p, string d, string dt, string t)
  {
    appointmentID = a;
    patientID = p;
    doctor = d;
    date = dt;
    time = t;
    status = "Pending";
    next = NULL;
  }
};

// Appointment linked list
Node *appointmentHead = NULL;

// Queue node
struct QueueNode
{
  int appointmentID;
  QueueNode *next;

  QueueNode(int id)
  {
    appointmentID = id;
    next = NULL;
  }
};

QueueNode *front = NULL;
QueueNode *rear = NULL;

// Add appointment ID to queue
void enqueue(int id)
{
  QueueNode *newNode = new QueueNode(id);

  if (front == NULL)
  {
    front = rear = newNode;
  }
  else
  {
    rear->next = newNode;
    rear = newNode;
  }
}

// Remove appointment ID from queue
int dequeue()
{
  if (front == NULL)
    return -1;

  QueueNode *temp = front;
  int id = temp->appointmentID;

  front = front->next;

  if (front == NULL)
    rear = NULL;

  delete temp;

  return id;
}

// Search appointment
Node *searchAppointment(int id)
{
  Node *temp = appointmentHead;

  while (temp != NULL)
  {
    if (temp->appointmentID == id)
      return temp;

    temp = temp->next;
  }

  return NULL;
}

// Add appointment
int addAppointment(int aID, int pID, string doctor,
                   string date, string time)
{
  if (aID <= 0 || pID <= 0 ||
      doctor.empty() || date.empty() || time.empty())
    return 0;

  // Check patient exists
  if (!patientExists(pID))
    return 0;

  // Check duplicate appointment ID
  if (searchAppointment(aID) != NULL)
    return 0;

  // Check doctor availability
  Node *temp = appointmentHead;

  while (temp != NULL)
  {
    if (temp->doctor == doctor &&
        temp->date == date &&
        temp->time == time &&
        (temp->status == "Pending" ||
         temp->status == "Scheduled"))
    {
      return 0;
    }

    temp = temp->next;
  }

  Node *newNode = new Node(aID, pID, doctor, date, time);

  // Insert at end
  if (appointmentHead == NULL)
  {
    appointmentHead = newNode;
  }
  else
  {
    temp = appointmentHead;

    while (temp->next != NULL)
      temp = temp->next;

    temp->next = newNode;
  }

  enqueue(aID);

  return 1;
}

// Update appointment
int updateAppointment(int id, string doctor,
                      string date, string time)
{
  if (doctor.empty() || date.empty() || time.empty())
    return 0;

  Node *temp = searchAppointment(id);

  if (temp == NULL)
    return 0;

  if (temp->status != "Pending" &&
      temp->status != "Scheduled")
    return 0;

  // Check doctor's availability
  Node *check = appointmentHead;

  while (check != NULL)
  {
    if (check->appointmentID != id &&
        check->doctor == doctor &&
        check->date == date &&
        check->time == time &&
        (check->status == "Pending" ||
         check->status == "Scheduled"))
    {
      return 0;
    }

    check = check->next;
  }

  temp->doctor = doctor;
  temp->date = date;
  temp->time = time;

  return 1;
}

// Process next appointment
int processNextAppointment()
{
  while (front != NULL)
  {
    int id = dequeue();

    Node *temp = searchAppointment(id);

    if (temp != NULL && temp->status == "Pending")
    {
      temp->status = "Scheduled";
      return 1;
    }
  }

  return 0;
}

// Cancel appointment
int cancelAppointment(int id)
{
  Node *temp = searchAppointment(id);

  if (temp == NULL)
    return 0;

  if (temp->status != "Pending" &&
      temp->status != "Scheduled")
    return 0;

  temp->status = "Cancelled";

  // Rebuild queue
  while (front != NULL)
    dequeue();

  temp = appointmentHead;

  while (temp != NULL)
  {
    if (temp->status == "Pending")
      enqueue(temp->appointmentID);

    temp = temp->next;
  }

  return 1;
}

// Complete appointment
int completeAppointment(int id)
{
  Node *temp = searchAppointment(id);

  if (temp == NULL)
    return 0;

  if (temp->status != "Scheduled")
    return 0;

  temp->status = "Completed";

  return 1;
}

// Display all appointments
void displayAppointments()
{
  if (appointmentHead == NULL)
  {
    cout << "\nNo appointments available.\n";
    return;
  }

  Node *temp = appointmentHead;

  cout << "\n========== APPOINTMENTS ==========\n";

  while (temp != NULL)
  {
    cout << "\nAppointment ID: " << temp->appointmentID;
    cout << "\nPatient ID: " << temp->patientID;
    cout << "\nDoctor: " << temp->doctor;
    cout << "\nDate: " << temp->date;
    cout << "\nTime: " << temp->time;
    cout << "\nStatus: " << temp->status;
    cout << "\n-----------------------------\n";

    temp = temp->next;
  }
}

// Display pending queue
void displayQueue()
{
  if (front == NULL)
  {
    cout << "\nQueue is empty.\n";
    return;
  }

  QueueNode *temp = front;

  cout << "\nPending Appointment Queue:\n";

  while (temp != NULL)
  {
    cout << temp->appointmentID << " -> ";
    temp = temp->next;
  }

  cout << "NULL\n";
}
// Load an appointment from the saved file
int loadAppointment(int aID, int pID, string doctor,
                    string date, string time, string status)
{
    if (aID <= 0 || pID <= 0 ||
        doctor.empty() || date.empty() || time.empty())
        return 0;

    if (!patientExists(pID))
        return 0;

    if (searchAppointment(aID) != NULL)
        return 0;

    if (status != "Pending" &&
        status != "Scheduled" &&
        status != "Completed" &&
        status != "Cancelled")
        return 0;

    Node *newNode = new Node(aID, pID, doctor, date, time);

    newNode->status = status;

    if (appointmentHead == NULL)
    {
        appointmentHead = newNode;
    }
    else
    {
        Node *temp = appointmentHead;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    // Only pending appointments enter the queue
    if (status == "Pending")
        enqueue(aID);

    return 1;
}
// Bubble sort appointments by ID
void bubbleSort()
{
  if (appointmentHead == NULL ||
      appointmentHead->next == NULL)
    return;

  int swapped;

  do
  {
    swapped = 0;
    Node *temp = appointmentHead;

    while (temp->next != NULL)
    {
      if (temp->appointmentID >
          temp->next->appointmentID)
      {
        int a = temp->appointmentID;
        temp->appointmentID = temp->next->appointmentID;
        temp->next->appointmentID = a;

        int p = temp->patientID;
        temp->patientID = temp->next->patientID;
        temp->next->patientID = p;

        string d = temp->doctor;
        temp->doctor = temp->next->doctor;
        temp->next->doctor = d;

        string dt = temp->date;
        temp->date = temp->next->date;
        temp->next->date = dt;

        string t = temp->time;
        temp->time = temp->next->time;
        temp->next->time = t;

        string s = temp->status;
        temp->status = temp->next->status;
        temp->next->status = s;

        swapped = 1;
      }

      temp = temp->next;
    }

  } while (swapped);
}

// Linear search
int linearSearch(int id)
{
  Node *temp = appointmentHead;
  int position = 0;

  while (temp != NULL)
  {
    if (temp->appointmentID == id)
      return position;

    position++;
    temp = temp->next;
  }

  return -1;
}

// Return appointment count for file.cpp
int getAppointmentCount()
{
  int count = 0;
  Node *temp = appointmentHead;

  while (temp != NULL)
  {
    count++;
    temp = temp->next;
  }

  return count;
}

// Get appointment details by position for file.cpp
int getAppointmentAt(int position, int &appointmentID, int &patientID,string &doctor, string &date, string &time,string &status)
{
  Node *temp = appointmentHead;
  int index = 0;

  while (temp != NULL)
  {
    if (index == position)
    {
      appointmentID = temp->appointmentID;
      patientID = temp->patientID;
      doctor = temp->doctor;
      date = temp->date;
      time = temp->time;
      status = temp->status;

      return 1;
    }

    index++;
    temp = temp->next;
  }

  return 0;
}

// Delete all appointments and queue nodes
void clearAppointments()
{
  Node *temp = appointmentHead;

  while (temp != NULL)
  {
    Node *nextNode = temp->next;
    delete temp;
    temp = nextNode;
  }

  appointmentHead = NULL;

  while (front != NULL)
    dequeue();

  rear = NULL;
}
