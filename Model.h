#pragma once
#include <vector>
#include "Node.h"
#include "Member.h"
#include "API/Include/ScadAPIX.hxx"


class Model {
public:
	/*Collection of nodes*/
	std::vector<Node> nodes;

	/*Collection of members*/
	std::vector<Member> members;

	// Default constructor
	Model();

	// Creates nodes
	void createNodes(ScadAPI&	handle) {
		// ����
		ApiNodeAddSize(handle, this->nodes.size());
		for (u_int i = 0; i < this->nodes.size(); i++) {
			ApiNodeUpdate(handle, this->nodes[i].id, this->nodes[i].x, this->nodes[i].y, this->nodes[i].z);
			ApiNodeSetName(handle, this->nodes[i].id, this->nodes[i].name.c_str());
		}
	}

	// Creates members
	void createMembers(ScadAPI&	handle) {
		// Add count of members
		ApiElemAdd(handle, this->members.size());

		// Update members
		u_int nodeArray[2];
		u_int elementArray[1];

		for (u_int i = 0; i < this->members.size(); i++) {
			nodeArray[0] = this->members[i].node1;
			nodeArray[1] = this->members[i].node2;
			ApiElemUpdate(handle, this->members[i].id, 5, 2, nodeArray);

			// Name
			ApiElemSetName(handle, this->members[i].id, this->members[i].name.c_str());

			// Section
			u_int section = ApiSetRigid(handle, this->members[i].section.c_str());
			elementArray[0] = this->members[i].id;
			ApiSetRigidElem(handle, section, 2, elementArray);

			// Pin1
	        ApiSetJoint(handle, this->members[i].pin1, this->members[i].id, this->members[i].node1, 0);
			ApiSetJoint(handle, this->members[i].pin2, this->members[i].id, this->members[i].node2, 0);
		}

		
	}
	
};
