#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct data_node {
	int id; // ²Ä´X­Ó¥[¶ivectorªº¸ê®Æ 
	int student_count; // ¾Ç¥Í¼Æ
	int graduate_count; // ²¦·~¥Í¼Æ 
	string school_name; // ¾Ç®Õ¦WºÙ
	string major_name; // ¬ì¨t¦WºÙ
	string day_night_e; // ¤é©]§O
	string day_night_c;
	string level_e; // µ¥¯Å§O 
	string level_c;
};

class tree_node {
private:
	std::vector<data_node> school_info; // ¾Ç®Õªº¸ê°T 
	tree_node* father = NULL; // ¤÷¤l¾ð 
	tree_node* greater_node = NULL; // ¥k¤l¾ð 
	tree_node* smaller_node = NULL; // ¥ª¤l¾ð 
	tree_node* middle_node = NULL; // ¤¤¤l¾ð 
	

public:
	void find_height(tree_node*& node ) { // smaller_node¬Oprivate¡A©Ò¥H¥Î¤@­Ómethod±Nnode«e©¹¥ª¤l¾ð¡A¥H­pºâ¾ð°ª 
		node = node->smaller_node;
	} 
	
	vector<data_node> get_info() {
		return school_info;
	}
	
	bool is_empty(tree_node* cur_node) { // ÀË¬d¶Ç¶i¨Óªº¾ð¬O§_¬°ªÅ 
		if (cur_node == NULL) {
			return true;
		}
		else {
			return false;
		}
	};
	
	bool is_full(std::vector<data_node> school_info) { // ½T»{¦¹¸`ÂI¬O¤£¬O¶W¹L2­Ó¡A»Ý­n°µ¤À¸Ñ
	
		// ÀË¬disfull & splitªº¿ù»~ 
	
		int count = 1; // ­Y¬Ocount(vector¸Ì¤£¦P¼Æ¦rªº¼Æ¶q)¹F¨ì¤T¡A¥Nªí°ª¹L23¾ðªº­­¨î¡A»Ý­n¶i¦æ¤Àµõ 
		int cur = school_info[0].graduate_count;
		for (int i = 0; i < school_info.size(); i++) {
			if (cur != school_info[i].graduate_count) {
				count++;
				cur = school_info[i].graduate_count;
			}
		}
		
		if (count > 2) {
			return true;
		}
		else {
			return false;
		}
	}
	
	void bubbleSort(std::vector<data_node>& school_info) { // ªwªj±Æ§Ç¡AÅý¾ð¸`ÂI¤¤ªºvector°}¦C¥Ñ¤p±Æ¨ì¤j 
    	int n = school_info.size();
    	if (school_info.size() == 1) {
    		return;
		}
    	
    	for (int i = 0; i < n-1; ++i) {
        	for (int j = 0; j < n-i-1; ++j) {
            	if (school_info[j].graduate_count > school_info[j+1].graduate_count) {
                	// ¥æ´«¤¸¯À
                	data_node temp = school_info[j];
                	school_info[j] = school_info[j+1];
                	school_info[j+1] = temp;
            	}
        	}
    	}
	}
	
	bool is_root(tree_node* cur_node){ // ÀË¬d¥Ø«eªºnode¬O§_¬°®Ú¸`ÂI
		if (cur_node->father == NULL) {
			return true;
		}
		else {
			return false;
		}
	};

	void split(tree_node* split_node) { // ¤À³Înode
	
		cout << "split start" << endl;
		cout << "all info:" << split_node->school_info[0].major_name << "=" << split_node->school_info[0].graduate_count << ", " << split_node->school_info[1].major_name << "=" << split_node->school_info[1].graduate_count  << ", " << split_node->school_info[2].major_name << "=" << split_node->school_info[2].graduate_count << endl;
		// ¤À³Î¤£¦P²¦·~¥Í¼Æªºnode 
		// ³Ì¤p 
		std::vector<data_node> smallest;
		smallest.push_back(split_node->school_info[0]);
		
		// ³Ì¤j 
		std::vector<data_node> greatest;
		greatest.push_back(split_node->school_info[split_node->school_info.size()-1]);
		
		// ¤¤¶¡ªº¥i¥H¤£³]ªì©l­È¡A¥u­n¤£µ¥©ó³Ì¤j©Î³Ì¤p´N¬O¤¤¶¡­È 
		std::vector<data_node> middle;
		
		for(int i = 0; i < split_node->school_info.size(); i++) { // ¦]¬°·|¦³¼Æ¦r­«½Æªº±¡ªp¡A©Ò¥H¤Àµõ®É¥i¯à¤£¥u¬O¤@­Ónode¦Ó¬O«Ü¦hnode 
			if (split_node->school_info[i].graduate_count == smallest[0].graduate_count) {
				smallest.push_back(split_node->school_info[i]);
			}
			else if (split_node->school_info[i].graduate_count == greatest[0].graduate_count) {
				greatest.push_back(split_node->school_info[i]);
			}
			else{
				middle.push_back(split_node->school_info[i]);
			}
			// 1.±q¤U©¹¤W°µ¡Asmall©Mgreat³£¤£¥Î°Ê¡Amiddle­n¦A¦Ò¼{ 
		}
		
		cout << "check copy:";
		cout << smallest[0].major_name << " & " << middle[0].major_name << " & " << greatest[0].major_name << endl;
		
		// ¶Ç¶i¨Óªº¸`ÂI¬Orootªº±¡ªp
		if (split_node->is_root(split_node)) {
			cout << "root" << endl;
			// ·s¼W¸`ÂI¡A±N¸`ÂI¤¤³Ì¤j¼Æ§@½Æ»s
			tree_node* new_great = new tree_node;
			new_great->school_info = greatest;
			cout << "greatest" << new_great->school_info[0].major_name << new_great->school_info[0].school_name << endl;
			
			// ·s¼W¸`ÂI¡A³]©w¤¤¶¡¼Æ(¤¤¶¡©¹¤W²¾¡A©Ò¥H·|¬O·sªºroot)
			split_node->father = new tree_node;
			split_node->father->school_info = middle;
			cout << "middle" << split_node->father->school_info[0].major_name << split_node->father->school_info[0].school_name << endl;
			
			// ±N­ì¥»ªº¸`ÂIÂà´«¬°¤À³Î«áªº¸`ÂI
			split_node->school_info = smallest;
			cout << "smallest" << split_node->school_info[0].major_name << split_node->school_info[0].school_name << endl;
			
			// ³]©w¦U­Ó¸`ÂIªº«ü¼Ð
			new_great->father = split_node->father;
			split_node->father = split_node->father;
			split_node->father->greater_node = new_great;
			split_node->father->smaller_node = split_node; // ¦¹®Éªºsplit node¥u·|³Ñ¤U¤À³Î®É³Ì¤pªº¼Æ­È 
		} 
		
		else {
			cout << "not root" << endl;
			// ·s¼W¸`ÂI¡A±N¸`ÂI¤¤³Ì¤j¼Æ§@½Æ»s
			tree_node* new_great = new tree_node;
			new_great->school_info = greatest;
			cout << "greatest" << new_great->school_info[0].major_name << new_great->school_info[0].school_name << endl;
			
			// ±N¤À³Î¥X¨Óªº¤¤¶¡­È(middle)µ¹¨ìparent
			split_node->father->school_info.push_back(middle[0]);
			split_node->father->bubbleSort(split_node->father->school_info);
			cout << "middle" << split_node->father->school_info[0].major_name << split_node->father->school_info[0].school_name << endl;
			
			// ±N­ì¥»ªº¸`ÂIÂà´«¬°¤À³Î«áªº¸`ÂI
			split_node->school_info = smallest;
			cout << "smallest" << split_node->school_info[0].major_name << split_node->school_info[0].school_name << endl;
			
			// ³]©w¦U­Ó¸`ÂIªº«ü¼Ð
			new_great->father = split_node->father;
			split_node->father->middle_node = new_great;
			
			// ÀË¬d·sªºparent node¦³¨S¦³»Ý­n¶i¦æsplitªº°Ê§@
			if (split_node->father->is_full(split_node->father->school_info)) {
				split_node->father->split(split_node->father);
			}
		}
		
	}

	void insert_node(tree_node*& root_node, data_node new_insert_data) { // ´¡¤J¸ê®Æ 
		// «Ø¥ß·s¸`ÂI 
		tree_node* cur_node = root_node;
		
		// ¦pªG¶Ç¶i¨Óªº¾ð¬OªÅ¤l¾ð
		if (is_empty(root_node)) {
			root_node = new tree_node;
			cur_node = root_node;
			cur_node->father = NULL;
		}
		
		// ¥ý´M§ä·sªº´¡¤J¸ê®Æ¥¿½Tªº´¡¤J¦ì¸m¡A±q®Ú¸`ÂIªº¦ì¸m´M§ä
		else {
			while (!is_empty(cur_node)) {
				if (cur_node->school_info.empty()) { // ªÅªºvector = ´¡¤J¨ì³o¸Ì 
					break;
				} 
				
				// ¦b¨C¦¸²¾°Ê«e¡A¥ý¨M©w¦nfatherªº«ü¦V¡AÀ³¸Ó­n¬O²¾°Ê«eªº¦Û¤v 
				cur_node->father = cur_node;
				if (new_insert_data.graduate_count < cur_node->school_info[0].graduate_count) { // ¤ñvector¸Ì³Ì¤pªºÁÙ¤p->¥ª¤l¾ð 
					if (is_empty(cur_node->smaller_node)) { // ©è¹F¸­¤l 
						break;
					}
					else {
						cur_node = cur_node->smaller_node;
					}
				}
			
				else if (new_insert_data.graduate_count > cur_node->school_info[cur_node->school_info.size()-1].graduate_count) { // ¤ñvector¸Ì³Ì¤jªºÁÙ¤j->¥k¤l¾ð
					if (is_empty(cur_node->greater_node)) { // ©è¹F¸­¤l 
						break;
					}
					else {
						cur_node = cur_node->greater_node;
					}
				}
				
				else { // «D¥ª«D¥k->¤¤¤l¾ð
					if (is_empty(cur_node->middle_node)) { // ©è¹F¸­¤l 
						break;
					}
					else {
						cur_node = cur_node->middle_node;
					}
				}
			}
		}
		
		// ¤W­±ªºµ{§Ç¨«§¹«á¡Acur_node¤w¸g¬O¥¿½Tªº´¡¤J¦ì¸m¤F 

		cur_node->school_info.push_back(new_insert_data); // ¥ý±N¸ê®Æ°ï¶ivector³Ì«á¤è
		
		cur_node->bubbleSort(cur_node->school_info); // ¥Îbubble sort½T«Ovector¸Ìªº¸ê®Æ¬O¥Ñ¤p¨ì¤j±Æ§Ç

		cout << "split check" << endl;
		if (cur_node->is_full(cur_node->school_info)) {
			cur_node->split(cur_node);
			cout << "split done" << endl;
		}
	}
};

void Infile(string fileName, vector<data_node>& student_count) { // Åª¤J¸ê®Æ¡Astudent_count¬°vector°}¦C¡A¸Ì­±ªº¸ê®Æ¤ÎÅª¤Jªº¸ê®Æ
	// ¥Îvector°}¦CÀx¦s¾Ç®Õ¸ê®Æ
	int data_num = 0; 
    string garbage;
	std::string line;
	
    data_node cur_data_node;
    // cur_data_node¬Oinfileªº¹ï¶H ¡A¦binfile¤§«á¦A±N¸ê®Æ±a¤Jvector
    int graduate = 0; // ¥ý¦b³o¸Ì«Å§i¡AÂÇ¥ÑinfileÀò±o¸ê®Æ¦A½Æ»s¶idata_node¸Ì 
    
    std::ifstream infile(fileName.c_str());
    
    // ¸ê®Æ¶}±Ò¥¢±Ñ 
    if (!infile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line); // ¸õ¹L±ÆÀY*3 
    
    int tokenCount = 0;
    
    while (infile >> garbage) {
    	// ¾Ç®Õ¥N½X¤£»Ý­n 
        infile >> cur_data_node.school_name; // ¾Ç®Õ¦WºÙ 
        infile >> garbage; // ¬ì¨t¥N½X¤£»Ý­n 
        infile >> cur_data_node.major_name; // ¬ì¨t¦WºÙ 
        infile >> cur_data_node.day_night_e; // ¤é©] 
        infile >> cur_data_node.day_night_c;
        infile >> cur_data_node.level_e; // µ¥¯Å 
        infile >> cur_data_node.level_c;
    	infile >> cur_data_node.student_count; // ¾Ç¥Í¼Æ 
        infile >> garbage; // ±Ð®v¼Æ¶q¤£»Ý­n 
        infile >> graduate; // ²¦·~¥Í¼Æ 
        
        data_num = data_num + 1;
        	
		cur_data_node.id = data_num; // id = §Ç¸¹(²Ä´X­ÓÅª¶iªº¸ê®Æ) 
        cur_data_node.graduate_count = graduate; // ²¦·~¥Í¼Æ 
        	
        student_count.push_back(cur_data_node); // pushback¨ìvector³Ì«á¤è´Nºâ§¹¦¨¤@µ§¸ê®ÆªºÅª¤J 
            
		// Åª¨ì­nªº¸ê®Æ«á¸õ¹L³Ñ¤Uªº 
        std::getline(infile, line);
            
        // ¨Ç³\±ø¥óªºªì©l¤Æ 
        tokenCount = 0;
                        
        // ¤U¤@¦æ­«·s¶}©l
    }
}

void build_tree(vector<data_node> student_count) {
	int cur_num = 0; // ¦L¥X´X­Ónode 
    int tree_height = 1; // ¾ð°ª
    int node_count = 0; // ¸`ÂI¼Æ
    tree_node* two_three_tree_root = NULL; // «Ø¥ß®Ú¸`ÂI 
    vector<data_node> print_node; // ¦L¥X¨Óªº¾Ç®Õ¸ê®Æ 
    
    for (int i = 0; i < student_count.size(); i++) {
        cout << "inserted" << i << endl;
        
        if (two_three_tree_root == NULL) {
            two_three_tree_root = new tree_node;
        }
        
        two_three_tree_root->insert_node(two_three_tree_root, student_count[i]);
        
    	tree_node* temp_root = two_three_tree_root;
    	print_node = temp_root->get_info();
    	cout << "root size: " << print_node.size() << endl;
    }
     
    print_node = two_three_tree_root->get_info();
    cout << "root size: " << print_node.size() << endl;
    
    cout << print_node[0].school_name << ", " << print_node[0].major_name << ", " << print_node[0].student_count << ", " << print_node[0].graduate_count << endl;
    cout << print_node[1].school_name << ", " << print_node[1].major_name << ", " << print_node[1].student_count << ", " << print_node[1].graduate_count << endl;
    cout << print_node[2].school_name << ", " << print_node[2].major_name << ", " << print_node[2].student_count << ", " << print_node[2].graduate_count << endl;
	/*   
	/*   
    tree_node* temp_root = two_three_tree_root;
    print_node = temp_root->get_info();
    
    while(temp_root != nullptr) {
    	tree_height++;
    	temp_root->find_height(temp_root);
	}
	
	cout << "Tree height = " << tree_height << endl; // ¦L¥X¾ð°ª 
	
	while(cur_num < print_node.size() - 1) {
		cout << cur_num << endl;
		cout << cur_num << ": " << "[" << print_node[cur_num].id << "] " << print_node[cur_num].school_name << ", " << print_node[cur_num].major_name << ", " << print_node[cur_num].day_night_e << " " << print_node[cur_num].day_night_c << ", " << print_node[cur_num].level_e << " " << print_node[cur_num].level_c << ", " << print_node[cur_num].student_count << ", " << print_node[cur_num].graduate_count << endl;
		cur_num++;
	}
	*/ 
}

int main() {
	
	int command = 0;
    
    std::vector<data_node> student_count;
    
    do {
    	cout << endl;
		cout << "********** Heap Construction **********" << endl;
		cout << "* 0. QUIT                             *" << endl;
		cout << "* 1. Build 23 tree                    *" << endl;
		cout << "* 2. Build AVL tree                   *" << endl;
		cout << "***************************************" << endl;
    
    	cout << "Input a choice(0, 1, 2):";
    	
    	cin >> command;
    	cout << endl;
    
    	std::string fileName;
    	if (command == 1) {
    		cout << "Input a file number ([0] Quit):";

    		// ±q¨Ï¥ÎªÌ¿é¤J¤¤Åª¨úÀÉ®×½s¸¹
    		cin >> fileName;
    		// ²Õ¦XÀÉ®×¦WºÙ	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		Infile(fileName, student_count);
    		build_tree(student_count);
		}
		
		/*
		if (command == 2) {
			cout << "Input a file number ([0] Quit):";
			
			// ±q¨Ï¥ÎªÌ¿é¤J¤¤Åª¨úÀÉ®×½s¸¹
    		cin >> fileName;
    		// ²Õ¦XÀÉ®×¦WºÙ	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";
			
    		student_count = student_count(fileName);
		}
		*/
				
		if (command == 0) {
			break;
		}
	} while (command != 0);

	return 0;
}
