#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> read_nat(const string &nat);
vector<string> read_flow(const string &flow);
vector<string> format_output(vector<string> &nat_vector, vector<string> &flow_vector);
void create_output(vector<string> &output_vector);

int main() {
  string nat_file, flow_file;
  vector<string> nat_vector, flow_vector, output_vector;

  cout << "Please input NAT file" << endl;
  cin >> nat_file;

  cout << "Please input FLOW file" << endl;
  cin >> flow_file;

  nat_vector = read_nat(nat_file);
  flow_vector = read_flow(flow_file);

  output_vector = format_output(nat_vector, flow_vector);

  create_output(output_vector);

  return 0;
}

// Scans NAT File and converts to an orderly vector
vector<string> read_nat(const string &nat) {
  vector<string> nat_vector;
  string file_msgs;
  ifstream in_file;

  in_file.open(nat.c_str());

  if (!in_file.is_open()) {
    exit(0);
  }

  while (in_file >> file_msgs) {
    nat_vector.push_back(file_msgs);
  }

  in_file.close();

  return nat_vector;
}

// Scans Flow File and converts to an orderly vector
vector<string> read_flow(const string &flow) {
  vector<string> flow_vector;
  string file_msgs;
  ifstream in_file;

  in_file.open(flow.c_str());

  if (!in_file.is_open()) {
    exit(0);
  }

  while (in_file >> file_msgs) {
    flow_vector.push_back(file_msgs);
  }

  in_file.close();

  return flow_vector;
}

// This is where all the translations occur
vector<string> format_output(vector<string> &nat_vector, vector<string> &flow_vector) {
  string star_before, star_after;
  vector<string> output_vector;
  for (unsigned i = 0; i < flow_vector.size(); i++) { // Loops through the Flow Inputs for NAT Table
    for (unsigned j = 0; j < nat_vector.size(); j++) { // Loops through NAT Table given one flow at a time
      if (nat_vector.at(j).find(flow_vector.at(i) + ",") != string::npos) { // Found a match
        output_vector.push_back(flow_vector.at(i) + " -> " + nat_vector.at(j).substr(nat_vector.at(j).find(",") + 1));
        break;
      }
      else if (nat_vector.at(j).find("*:") != string::npos) { // If a "*" is located before the ";"
        star_before = nat_vector.at(j).substr(nat_vector.at(j).find("*:") + 1, nat_vector.at(j).find(",") -1); // Copy the NAT's Port to be translated
        if (flow_vector.at(i).find(star_before) != string::npos) { // We check to see if the current Flow has a match to the current NAT's Port
          output_vector.push_back(flow_vector.at(i) + " -> " + nat_vector.at(j).substr(nat_vector.at(j).find(",") + 1));
          break;
        }
      }
      else if (nat_vector.at(j).find(":*") != string::npos) { // If a "*" is located after the ":"
        star_after = nat_vector.at(j).substr(0, nat_vector.at(j).find(":")); // Copy the NAT's IP to be translated
        if (flow_vector.at(i).find(star_after) != string::npos) { // We check to see if the current Flow has a match to the current NAT's IP
          output_vector.push_back(flow_vector.at(i) + " -> " + nat_vector.at(j).substr(nat_vector.at(j).find(",") + 1));
          break;
        }
      }
      if (j == nat_vector.size() - 1) { // No match ever found
        output_vector.push_back("No nat match for " + flow_vector.at(i));
      }
    }
  }
  return output_vector;
}

// Create the OUTPUT file given the output vector
void create_output(vector<string> &output_vector) {
  ofstream output_file;
  output_file.open("OUTPUT");
  for (unsigned i = 0; i < output_vector.size(); i++) {
    output_file << output_vector.at(i) << endl;
  }
  output_file.close();
}