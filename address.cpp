#include <iostream>
template <typename T>
void print(T msg, int b=0) {
	if(b==0) {
		std::cout<<msg;
	}
	else {
		std::cout<<msg<<std::endl;
	}
}
/*
void print(const char* msg) {         
	std::cout << msg;
}
void print(const char msg) {
	std::cout << msg;
}
void print(const int msg) {
	std::cout << msg;
}
void input(char* msg) {
	std::cin >> msg;
}
void input(int msg) {
	std::cin >> msg;
}
void input(char msg) {
	std::cin >> msg;
}

void inOutput(const char* msg) {
	print(msg);
	input(msg);
}
*/




int strcmp(char* st1, char* st2) { //두 문자열이 다르면 -> return 0
	int i=0; 
	for(i=0;*(st1+i)!='\0'&&*(st2+i)!='\0';i++) {
		if(*(st1+i) != *(st2+i)) {
			return 0;
		}
	}
	if(*(st1+i) != *(st2+i)) {
		return 0;
	}
	else {
		return 1;
	}
}

int strlen(char* origin) {
	int length=0;
	while(*(origin+length)!='\0') {
		length++;
	}
	return length;
}

char* strcpy(char* origin) {
	int length = strlen(origin)+1;
	char* new_string = new char[length];
	for(int i=0; i<length; i++) {
		*(new_string + i) = *(origin + i);
	}
	return new_string;
}


/*
class IOprint {
	private:
		int select;
	public:

};*/

class Account {
	private:
		int user_id;
		char* user_name;
		int user_money;
	public:
		Account(){}
		Account(int user_id, char* user_name, int user_money) { //동적
			this->user_id = user_id;

			this->user_name = user_name;
			this->user_money = user_money;
		}
		int getUserId() {
			return this->user_id;
		} 
		char* getUserName() {
			return this->user_name;
		}             
		int getUserMoney() {
			return this->user_money;
		}
		void setUserID(int id) {
			this->user_id = id;
		}                                                         
		void setUserName(char* name) {
			this->user_name = name;
		}
		void setUserMoney(int money) {
			this->user_money = money;
		}
		void addUserMoney(int money) {
			this->user_money += money;
		}
		void minusUserMoney(int money) {
			this->user_money -= money;
		}
		~Account() {
		}
};

class AccountNode {
	private:
		Account* user_instance;
		AccountNode* link;
	public:
		AccountNode() {}
		AccountNode(int user_id, char* user_name, int user_money, AccountNode* link = NULL) {
			user_instance = new Account (user_id, user_name, user_money);
		}
		AccountNode* getLink() {
			return link;
		}
		void setLink(AccountNode* node) {
			link = node;
		}
		Account* getUserInstance() {
			return user_instance;
		}
};

class LinkedList {
	private:
		AccountNode* account_head_node;
	public:
		LinkedList(){this->account_head_node=NULL;};
		LinkedList(AccountNode* account_node) {
			this->account_head_node = account_head_node;
		}
		AccountNode* set_account_head_node() {
			this->account_head_node = account_head_node;
		}
		AccountNode* get_account_head_node() {
			return account_head_node;
		}
		void addNode() {

		}

};

class AccountHandler {
	private:
		LinkedList* linked_list;
	private:
		void getAccountHeadNode() {
			
		}
		void findAccount(AccountNode* linked_list) {

		}
		void addAccount(int tmp_user_id, char* tmp_user_name, int tmp_user_money) {

		}

};

		

class Bank {
	private:
		char* bank_name;
		float commission;
		int limit_money;
		AccountNode* head_user_node;

	public:
		Bank() {}
		Bank(char* bank_name, int commission, int limit_money) {
			head_user_node = NULL;
			this->bank_name = bank_name;
			this->commission = commission;
			this->limit_money = limit_money;
		}
		void makeAccount(int tmp_user_id, char* tmp_user_name, int tmp_user_money) {
			if (head_user_node == NULL) {
				head_user_node =  new AccountNode(tmp_user_id, tmp_user_name, tmp_user_money);
			}
			else {
				AccountNode* tmp_node = head_user_node;
				while(tmp_node->getLink() != NULL) {
					tmp_node = tmp_node->getLink();
				}
				tmp_node->setLink(new AccountNode(tmp_user_id, tmp_user_name, tmp_user_money));
			}
		}
		char* getBankName() {
			return bank_name;
		}
		AccountNode* getHeadNode() {
			return head_user_node;
		}
		void setHaedNode(AccountNode* user_node) {
			this->head_user_node = user_node;
		}
		float getCommission() {
			return commission;
		}
		int  getLimitMoney() {
			return limit_money;
		}

		AccountNode* findNodeOfID(int id) { //찾으면 Node* 반환, 못찾으면 NULL	반환
			int flag = 0;
			AccountNode* tmp_node = head_user_node;
			if(tmp_node == NULL) {
				return NULL;
			}
			while(tmp_node!=NULL) {
				if (tmp_node->getUserInstance()->getUserId()==id) {
					flag = 1;
					break;
				}
				tmp_node = tmp_node->getLink();
			}
			if (flag == 0) {
				return NULL;
			}
			else {
				return tmp_node;
			}
		}

		int isMoneyPositive(int money) {
			return money>0;
		}

		void deposit(AccountNode* node, int money) {
			node->getUserInstance()->addUserMoney(money);
		}

		void withdraw(AccountNode* node, int money) {
			node->getUserInstance()->minusUserMoney(money);
		}

		int canwithdraw(AccountNode* node, int money) {
			return node->getUserInstance()->getUserMoney() >= money;
		}

		void bankTransfer(AccountNode* node1, AccountNode* node2, int money) {

		}

		AccountNode* traverse(AccountNode* tmp_node) {
			if(tmp_node == NULL) {
				return NULL;
			}
			else {
				tmp_node = tmp_node->getLink();
				return tmp_node;
			}
		}
};
 
class BankNode {
	private:
		Bank* bank;
		BankNode* link;
	public:
		BankNode(Bank* bank) {
			this->bank = bank;
			link = NULL;
		}
		BankNode* getLink() {
			return link;
		}
		void setLink(BankNode* bank_node) {
			this->link = bank_node;
		}
		Bank* getBank() {
			return bank;
		}
		void setBank(Bank* bank) {
			this->bank = bank;
		}
};

class ATM {
	private:
		BankNode* head_bank_node;
	public:
		ATM() {
			head_bank_node = NULL;
		}
		BankNode* getHeadBankNode() {
			return head_bank_node;
		}
		BankNode* findBank(char* bank_name) { //못찾으면 NULL
			int ishere = 0;
			if(head_bank_node == NULL) {
				return NULL;
			}
			else {
				BankNode* tmp_node1 = head_bank_node;
				while(tmp_node1 != NULL) {
					if (strcmp(tmp_node1->getBank()->getBankName(), bank_name)) {
						ishere = 1; //같은
						break;
					}
					else {
						tmp_node1 = tmp_node1->getLink();
					}
				}
				if(ishere == 1) {
					return tmp_node1;
				}
				else {
					return NULL;
				}
			}
		}
		void makeBank(Bank* bank) {
			if(findBank(bank->getBankName()) == NULL) { //	NULL -> bank 발견 x;
				if(head_bank_node == NULL) {
					head_bank_node = new BankNode(bank);
				}
				else {
					BankNode* tmp_node = head_bank_node;
					while(tmp_node->getLink() != NULL) {
						tmp_node = tmp_node->getLink();
					}
					tmp_node->setLink(new BankNode(bank));
				}
			}
		}
		int makeAccount(int tmp_user_id,char* tmp_bank_name,char* input_tmp_user_name,int tmp_user_money) {
			if(tmp_user_money<0) {
				return 2;
			}
			int length = 0;
			if(findBank(tmp_bank_name)->getBank()->findNodeOfID(tmp_user_id) == NULL) {
				char* name;
				name = strcpy(input_tmp_user_name);
				findBank(tmp_bank_name)->getBank()->makeAccount(tmp_user_id, name, tmp_user_money);
				return 0;
			}
			else {
				return 1;
			}
		}

		int deposit(char* bank_name, int user_id, int money) {
			if(findBank(bank_name)->getBank()->findNodeOfID(user_id)==NULL) { // 목표 계좌가 존재하지 않으면 0반환
				return 0;  
			}
			if(money <= 0) {
				return 1; // 0이하 입금시 비정상적 입금금액 출력
			}
			if(money > findBank(bank_name)->getBank()->getLimitMoney()){ // 최대한도를 넘어서 입금
				return 2;
			}
            findBank(bank_name)->getBank()->findNodeOfID(user_id)->getUserInstance()->addUserMoney(money);
			return 3;
		}

		int withdraw(char* bank_name, int user_id, int money) {
			if(findBank(bank_name)->getBank()->findNodeOfID(user_id)==NULL) { // 목표 계좌가 존재하지 않으면
				return 0;
			}
			if(money <=0) { //money > findBank(bank_name)->getBank()->getLimitMoney()
				return 1; // 출금 금액이 0 이하인 경우 오류 출력
			}
			if(money > findBank(bank_name)->getBank()->findNodeOfID(user_id)->getUserInstance()->getUserMoney()) { // 잔고부족: 입금할 금액이 더 잔고보다 더 큰 경우
				return 2;
			}
			findBank(bank_name)->getBank()->findNodeOfID(user_id)->getUserInstance()->minusUserMoney(money);
			return 3;
		}

		int accountTransfer(char* bank_name, char* target_bank_name, int user_id, int target_id, int money) {
			if(findBank(bank_name)->getBank()->findNodeOfID(user_id)==NULL) { //출금 계좌가 존재하지 않으면
				return 0;
			}
			if(findBank(target_bank_name) == NULL) { //목표 은행이 존재하지 않으면
				return 1;
			}
			if(findBank(target_bank_name)->getBank()->findNodeOfID(target_id)==NULL) { // 목표 계좌가 존재하지 않으면
				return 2;
			}
			if (money <= 0) { // 입금할 금액이 0이하이면
				return 3;
			}
			if(money > findBank(bank_name)->getBank()->findNodeOfID(user_id)->getUserInstance()->getUserMoney()) { // 잔고부족: 입금할 금액이 더 잔고보다 더 큰 경우
				return 4;
			}
			Account* tmp_target_user;
			Account* tmp_user;
			tmp_target_user = findBank(target_bank_name)->getBank()->findNodeOfID(target_id)->getUserInstance();
			tmp_user = findBank(bank_name)->getBank()->findNodeOfID(user_id)->getUserInstance();
			if(strcpy(bank_name, target_bank_name) == 0) { // 두 은행 이름이 다르면,
				tmp_user->minusUserMoney(money);
				tmp_target_user->addUserMoney(money * (1-(findBank(target_bank_name)->getBank()->getCommission()*0.01)));
				return 5;
			}
			else { // 두 은행 이름이 같으면,
				tmp_user->minusUserMoney(money);
				tmp_target_user->addUserMoney(money);
				return 6;
			}
		}
};

int main(void) {
	ATM atm;
	Bank bank;
	Bank* bank_pointer;
	AccountNode* tmp_user_node;
	BankNode* tmp_bank_node;
	int select=0;
	int user_id, target_id;
	char* user_name, *target_name;
	int money;
	char* bank_name, *target_bank_name;
	float commission;
	int limit_money;
	char input_target_bank_name[100];
	char input_user_name[100];
	char input_bank_name[100];

	
	while(select != 6) {
		std::cout<<"접속할 은행을 선택하세요 [ex: 농협, 신한 등등]: ";
		std::cin>>input_bank_name;
		bank_name=strcpy(input_bank_name);
		if (atm.findBank(bank_name) == NULL) {
			std::cout<<"해당 은행의 수수료를 입력하세요 (0~100): ";
			std::cin>>commission;
			if(commission<0 || commission>100) {
				std::cout<<"올바른 은행의 수수료를 입력하세요"<<std::endl;
				continue;
			}
			std::cout<<"해당 은행의 최대 한도를 입력하세요: ";
			std::cin>>limit_money;
		}
		atm.makeBank(new Bank(bank_name, commission, limit_money));

		
		std::cout<<"-----Menu-----"<<std::endl;
		std::cout<<"1.계좌개설"<<std::endl;
		std::cout<<"2.입금"<<std::endl;
		std::cout<<"3.출금"<<std::endl;
		std::cout<<"4.계좌이체"<<std::endl;
		std::cout<<"5.계좌번호 전체 출력"<<std::endl;
		std::cout<<"6.프로그램 종료"<<std::endl<<std::endl;
		std::cout<<"선택: ";
		std::cin>>select;
		if(select == 1) {
			std::cout<<"[계좌개설]"<<std::endl;
			std::cout<<"계좌ID: ";
			std::cin>>user_id;
			std::cout<<"이름: ";
			std::cin >> input_user_name;
			user_name = strcpy(input_user_name);
			std::cout<<"입금액: ";
			std::cin>>money;
			switch (atm.makeAccount(user_id,bank_name,user_name, money)) {
				case 0: print("정상 생성"); break;
				case 1: print("중복 계좌id가 존재합니다."); break;
				case 2: print("정상 금액을 입력하세요"); break;
			}
		}
		
		else if(select == 2) {
			std::cout<<"[입금]"<<std::endl;
			std::cout<<"계좌ID: ";
			std::cin>>user_id;
			std::cout<<"입금액: ";
			std::cin>>money;
			switch(atm.deposit(bank_name, user_id, money)) {
				case 0: std::cout<<"해당 계좌id가 존재하지 않습니다."<<std::endl; break;
				case 1: std::cout<<"0보다 큰 금액을 입력하세요."<<std::endl; break;
				case 2:	std::cout<<"촤대 한도를 넘어서 입금하셨습니다."<<std::endl; break;
				default: std::cout<<"입금완료"<<std::endl; break;
			}
		}

		else if(select == 3) {
			std::cout<<"[출금]"<<std::endl;
			std::cout<<"계좌ID: ";
			std::cin>>user_id;
			std::cout<<"출금액: ";
			std::cin>>money;
			switch(atm.withdraw(bank_name, user_id, money)) {
				case 0: std::cout<<"해당 계좌id가 존재하지 않습니다."<<std::endl; break;
				case 1: std::cout<<"0보다 큰 금액을 입력하세요."<<std::endl; break;
				case 2: std::cout<<"잔고가 부족합니다."<<std::endl; break;
				default: std::cout<<"출금 완료"<<std::endl; break;
			}
		}

		else if(select == 4) {
			std::cout<<"[계좌이체]"<<std::endl;
			std::cout<<"출금 계좌ID 입력: ";
			std::cin>>user_id;
			std::cout<<"입금할 은행 선택: ";
			std::cin>>input_target_bank_name;
			target_bank_name = strcpy(input_target_bank_name);
			std::cout<<"입금 계좌ID 입력: ";
			std::cin>>target_id;
			std::cout<<"입금액: ";
			std::cin>>money;
			switch(atm.accountTransfer(bank_name, target_bank_name, user_id, target_id, money)) {
				case 0: std::cout<<"출금 계좌id가 존재하지 않습니다."<<std::endl; break;
				case 1: std::cout<<"해당 은행사가 존재하지 않습니다."<<std::endl; break;
				case 2: std::cout<<"상대 계좌id가 존재하지 않습니다."<<std::endl; break;
				case 3: std::cout<<"올바르지 못한 입력입니다. 0보다 큰 금액을 입력하세요."<<std::endl; break;
				case 4: std::cout<<"현재 잔고 금액보다 큰 값을 입력하셨습니다. 다시 입력하세요."<<std::endl; break;
				default: std::cout<<"입금완료"<<std::endl; break;
			}
		}
		else if(select == 5) {
			tmp_user_node = atm.findBank(bank_name)->getBank()->getHeadNode();
			if(tmp_user_node==NULL) {
				print("유저 정보가 없다.");
				print(10);
			}
			else {
				std::cout<<tmp_user_node->getUserInstance()->getUserId()<<std::endl;
				std::cout<<tmp_user_node->getUserInstance()->getUserName()<<std::endl;
				std::cout<<tmp_user_node->getUserInstance()->getUserMoney()<<std::endl<<std::endl;

				while(atm.findBank(bank_name)->getBank()->traverse(tmp_user_node) != NULL) {
					tmp_user_node=atm.findBank(bank_name)->getBank()->traverse(tmp_user_node);
					std::cout<<tmp_user_node->getUserInstance()->getUserId()<<std::endl;
					std::cout<<tmp_user_node->getUserInstance()->getUserName()<<std::endl;
					std::cout<<tmp_user_node->getUserInstance()->getUserMoney()<<std::endl<<std::endl;
					std::cout<<"~~~~~~~~~~"<<std::endl<<std::endl<<std::endl;
				}
			}
		}
	}	
}