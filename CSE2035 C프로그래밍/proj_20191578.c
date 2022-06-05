#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct {
	int lv_HP; //���� ���������� ü��
	int cur_HP; //���� ���¿����� ü��
	int HP; //ü��
	int Attack; //����
	int Block; //���
	int Contact; //Ư������
	int Defence; //Ư�����
	int Speed; //���ǵ�
	int iv; //���� ��(0~31)
} Stat;

typedef struct {
	int lv; //����
	int dex_num; //���� ��ȣ
	char name[20]; //���ϸ� �̸�
	char type1[30]; //Ÿ��1
	char type2[30]; //Ÿ��2
	int dex_state; //0->������ ��ϵ��� ����, 1->�߰���, 2->��Ҵ�
	int exp; //����ġ
	Stat stat; //����
	struct POKE* link;
} POKE;

typedef struct {
	char user_name[10]; //����� �̸�
	POKE* poke; //����ڰ� ���� ���ϸ�(�ִ� 6����)
	int num_poke; //����ڰ� ���� ���� ���ϸ��� ��
} User;

POKE** head; //��� ���ϸ��� ��ȭ ������ ����
POKE* box; //���ϸ� �ڽ�

void fill_head(POKE** head); //head�� ��� ���ϸ��� ��ȭ ������ �����ϴ� �Լ�
void combine_node(POKE*, POKE*); //node1 �ڿ� node2�� ���̴� �Լ�
void PrintAll(POKE*); //����Լ�

void Battle(User* user); //���ϸ� ��Ʋ
int Fight(POKE* adversary, User* user, POKE* cur);
	//adversary: �������� ������ �߻� ���ϸ�
	//cur: user�� ���� ���ϸ�
	//��Ʋ ��Ȳ return
void Catch(POKE* adversary, User* user, POKE* curr); //�߻����ϸ� adversary�� ��ȹ
int Run(); //����ĥ �� ������ ����, ������ ��Ʋ ���


void Pokedex(); //���ϸ� ���� ��Ȳ ���
void user_Pokemon(POKE* poke, User* user); //user�� ���� ���ϸ�� ����
void Report(User* user); //������� ���� ���(����Ʈ)
void Pokecen(User* user); //���ϸ� ü�� ȸ��

int main(void) {
	//head�ȿ� ���� ���� ä���
	head = (POKE * *)malloc(78*sizeof(POKE*));
	for (int i = 0; i < 78; i++) {
		head[i] = (POKE*)malloc(sizeof(POKE));
		head[i]->link=NULL;
	}
	fill_head(head);
/*	printf("=======================================\n\n");
	for (int i = 0; i < 78; i++) {
		PrintAll(head[i]);
	}*/
	//printf("%s\n", ((POKE*)(head[0]->link))->name);

	//���� ����
	User *user=(User*)malloc(sizeof(User));
	user->poke = (POKE*)malloc(6 * sizeof(POKE));
	user->num_poke = 0;
	int order, starting;
	int next;
	printf("+----------Pokemon R&AS----------+\n");
	printf("+  �޴��� �������ּ���.          +\n");
	printf("+  1. ���� �����Ѵ�.             +\n");
	printf("+  2. ����.                      +\n\n");
	printf("+  >> ");
	scanf("%d", &order);
	if (order == 1) {
		printf("\n+------------New Game------------+\n");
		printf("+ ����� �̸��� �Է����ּ���.    +\n");
		printf("+ >> ");
		scanf("%s", &(user->user_name));
		printf("\n+ ��Ÿ�� ���ϸ��� �������ּ���.  +\n");
		printf("+--------------------------------+\n");
		printf("+ 1. Bulbasaur (Type1 : Grass, Type2 : Poison)\n");
		printf("+ 2. Charmander (Type : Fire)\n");
		printf("+ 3. Squirtle (Type : Water)\n");
		printf("+--------------------------------+\n");
		printf("+ >> ");
		scanf("%d", &starting);
		starting--;
		user->num_poke++;

		//user�� ù��° ���ϸ� ���� �ű��
		(user->poke[0]).link = NULL;
		(user->poke[0]).dex_num = ((POKE*)(head[starting]->link))->dex_num;
		strcpy((user->poke[0]).name, ((POKE*)(head[starting]->link))->name);
		strcpy((user->poke[0]).type1, ((POKE*)(head[starting]->link))->type1);
		strcpy((user->poke[0]).type2, ((POKE*)(head[starting]->link))->type2);
		(user->poke[0]).exp= ((POKE*)(head[starting]->link))->exp;
		(user->poke[0]).stat.HP = ((POKE*)(head[starting]->link))->stat.HP;
		(user->poke[0]).stat.Attack = ((POKE*)(head[starting]->link))->stat.Attack;
		(user->poke[0]).stat.Block = ((POKE*)(head[starting]->link))->stat.Block;
		(user->poke[0]).stat.Contact = ((POKE*)(head[starting]->link))->stat.Contact;
		(user->poke[0]).stat.Defence = ((POKE*)(head[starting]->link))->stat.Defence;
		(user->poke[0]).stat.Speed = ((POKE*)(head[starting]->link))->stat.Speed;
		(user->poke[0]).lv = 5;
		(user->poke[0]).dex_state = 2;
		((POKE*)(head[starting]->link))->dex_state = 2;
		
		int random;
		srand(time(NULL));
		random = rand() % 32;
		(user->poke[0]).stat.iv = random;
		(user->poke[0]).stat.lv_HP = ((((user->poke[0]).stat.HP) * 2) + random) * ((user->poke[0]).lv) / 100 + ((user->poke[0]).lv) + 10;
		(user->poke[0]).stat.cur_HP = (user->poke[0]).stat.lv_HP;
		//		printf("�������� %d(��)�� ���Դ�.\n", random);
//		printf("��Ÿ�� ���ϸ��� HP�� �� %d(��)��.\n", (user->poke[0]).stat.lv_HP);
//		printf("��Ÿ�� ���ϸ��� ������ %d(��)��.\n", (user->poke[0]).lv);
		Report(user);
		while (1) {
			printf("+-----------Main Menu------------+\n");
			printf("+ �޴��� �������ּ���.           +\n");
			printf("+ 1. ��Ʋ.                       +\n");
			printf("+ 2. ����.                       +\n");
			printf("+ 3. ���� ���ϸ�.                +\n");
			printf("+ 4. ���ϸ� ����.                +\n");
			printf("+ 5. ����Ʈ.                     +\n");
			printf("+ 6. ����.                       +\n");
			printf("+ >> ");
			scanf("%d", &next);
			if (next == 1) {
				//��Ʋ
				Battle(user);
			}

			else if (next == 2) {
				//����(���ϸ� ���� ��Ȳ ���)
				Pokedex();
			}

			else if (next == 3) {
				//���� ���ϸ�(����)
				user_Pokemon(user->poke, user);
			}

			else if (next == 4) {
				//���ϸ� ����(���ϸ� ȸ��, �ڽ� ����)
				Pokecen(user);
			}

			else if (next == 5) {
				//����Ʈ
				Report(user);
			}

			else if (next == 6) {
				//����
				break;
			}
		}
	}
	else {
		//���� ����
	}
	
	return 0;
}

void Report(User* user) {
	FILE* fp;
	fp = fopen("log.txt", "w");
	//���Ͽ� ���
	fprintf(fp, "+--------------Report--------------+\n");
	fprintf(fp, "+ ��������� ������ ����մϴ�.  +\n");
	fprintf(fp, "+ Ʈ���̳� �� = [%s]\n", user->user_name);
	fprintf(fp, "+ ���� ���ϸ� = \n");
	POKE* cur;
	cur = user->poke;
	int j = 1;
	while (1) {
		fprintf(fp, "%d. %s ", j++, cur->name);
		if (cur->type2[0] != '0') {
			fprintf(fp, "(Type1 : %s, Type2 : %s)\n", cur->type1, cur->type2);
		}
		else {
			fprintf(fp, "(Type : %s)\n", cur->type1);
		}
		if (cur->link == NULL) break;
		cur = cur->link;
	}
	fprintf(fp, "\n+----------------------------------+\n");
	fclose(fp);

	//�ܼ�â ���
	printf("+-------------Report-------------+\n");
	printf("+ ��������� ������ ����մϴ�.  +\n");
	printf("+ Ʈ���̳� �� = [%s]\n", user->user_name);
	printf("+ ���� ���ϸ� = \n");
	POKE* curr;
	curr = user->poke;
	int i = 1;
	while (1) {
		printf("%d. %s ", i++, curr->name);
		if (curr->type2[0] != '0') {
			printf("(Type1 : %s, Type2 : %s)\n", curr->type1, curr->type2);
		}
		else {
			printf("(Type : %s)\n", curr->type1);
		}
		if (curr->link == NULL) break;
		curr = curr->link;
	}
	printf("\n+--------------------------------+\n");
}



void Battle(User* user) {
	//��Ʋ
	//������ �߻� ���ϸ� �����ϱ�
	POKE* adversary;
	adversary = (POKE*)malloc(sizeof(POKE));
	int random;
	int lv_random;
	int iv_random;
	int i = 0;
	int battle_order;
	srand(time(NULL));
	random = rand() % 151;
	lv_random = (rand() % 7) - 3;
	iv_random = rand() % 32;
//	printf("�߻��� ���ϸ� ������ȣ: %d\n", random + 1);
//	printf("�߻��� ���ϸ� ������ ����� ���ϸ�� %d��ŭ ���̳���.\n", lv_random);
	POKE* curr = head[i];
	curr = curr->link;
	while (1) {
		if (curr->dex_num == random + 1) {
			adversary = curr;
			adversary->dex_state = 1;
			curr->dex_state = 1; //�߰��ߴ�!
			adversary->lv = user->poke[0].lv + lv_random;
			adversary->stat.iv = iv_random;
			adversary->stat.lv_HP = ((curr->stat.HP) * 2 + iv_random) * adversary->lv / 100 + 10 + adversary->lv;
			adversary->stat.cur_HP = adversary->stat.lv_HP;
			break;
		}
		curr = curr->link;
		if (curr == NULL) {
			i++;
			curr = head[i];
		}
	}


	//��Ʋ ����
	printf("+-----------Battle-----------+\n");
	printf("+ ��! �߻��� %s(Lv.%d)�� ��Ÿ����!\n", adversary->name, adversary->lv);
	while (1) {
		printf("+ ������ �ұ�? > 1. �ο��.\n");
		printf("+              > 2. ���ϸ�.\n");
		printf("+              > 3. ��´�.\n");
		printf("+              > 4. ����ģ��.\n");
		printf("+              >> ");
		scanf("%d", &battle_order);
		int fight_result, run_result;
		if (battle_order == 1) {
			//�ο��
			//���� �տ�������, ü���� 0�� �ƴ� ���ϸ�
			POKE* my = user->poke;
			while (my != NULL) {
				if (my->stat.cur_HP != 0) {
					break;
				}
				my = my->link;
			}
			//printf("��Ʋ�� ���� ���ϸ�: %s\n", my->name);

			fight_result = Fight(adversary, user, my);
			if (fight_result == 1) break;
			else if (fight_result == 2) {
				printf("�� �̻� ����� ���ϸ��� �����ϴ�.\n");
				break;
			}
		}

		else if (battle_order == 2) {
			//���ϸ�
			user_Pokemon(user->poke, user);
		}

		else if (battle_order == 3) {
			//��´�
			Catch(adversary, user, user->poke);
			if (adversary->stat.cur_HP == 0) break;
		}

		else if (battle_order == 4) {
			//����ģ��
			run_result = Run();
			if (run_result == 1) {
				break;
			}
		}
	}
}



int Fight(POKE* adversary, User* user, POKE* cur) {
	//adversary(�߻����ϸ�)�� cur(�� ���ϸ�)�� ��Ʋ

	//��뿡�� ���� �� �ִ� ���ط� damage
	int damage1, damage2; //damage1�� �߻����ϸ��� ������, damage2�� ���� �߻����ϸ�����
	int p, random;
	srand(time(NULL));
	p = rand() % 2; //p=0�̸� ����, p=1�̸� Ư������
	random = rand() % 5;
	if (p == 0) {
		//�׳� ����, �׳� ���
		damage1 = ((((adversary->lv * 2) / 5 + 2) * adversary->stat.Attack) / cur->stat.Block / 50 + 2) + random;
		damage2 = ((((cur->lv * 2) / 5 + 2) * cur->stat.Attack) / adversary->stat.Block / 50 + 2) + random;
	}
	else {
		//Ư�� ����, Ư�� ���
		damage1 = ((((adversary->lv * 2) / 5 + 2) * adversary->stat.Contact) / cur->stat.Defence / 50 + 2) + random;
		damage2 = ((((cur->lv * 2) / 5 + 2) * cur->stat.Contact) / adversary->stat.Defence / 50 + 2) + random;
	}
	//�߻����ϸ��� ����Ʈ���� ���� ����ġ
	int exp;
	exp = (adversary->lv * adversary->stat.HP) / 5;
	int level_up;
	level_up = cur->lv * cur->lv * cur->lv;

	int flag = 0; //��Ʋ ����� flag=1, flag=2�̸� ���ϸ��� �� ������
	//���ݽ���!!!!!!!!

	if (adversary->stat.Speed >= cur->stat.Speed) {
		//�߻� ���ϸ� ����
		if (adversary->stat.cur_HP > 0 && cur->stat.cur_HP > 0) {
			cur->stat.cur_HP -= damage1;
			if (cur->stat.cur_HP > 0) {
				printf("+ %s�� %s���� %d�� ���ظ� ������!\n", adversary->name, cur->name, damage1);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
			
				adversary->stat.cur_HP -= damage2;
				if (adversary->stat.cur_HP > 0) {
					printf("+ %s�� %s���� %d�� ���ظ� ������!\n", cur->name, adversary->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				}
				else {
					adversary->stat.cur_HP = 0;
					cur->exp += exp;
					printf("+ %s�� %s���� %d�� ���ظ� ������!\n", cur->name, adversary->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
					printf("+ %s�� ����Ʈ�ȴ�!\n", adversary->name);
					printf("+ %s�� %d��ŭ�� ����ġ�� �����!\n", cur->name, exp);
					//printf("+ %s�� ���� ����ġ: %d\n", cur->name, cur->exp);

					int find = 0;
					POKE* grow = (POKE*)malloc(sizeof(POKE));
					for (int i = 0; i < 78; i++) {
						grow = head[i];
						while (grow != NULL) {
							if (grow->dex_num == cur->dex_num) {
								//printf("ã�Ҵ� %s!\n", grow->name);
								find = 1;
								break;
							}
							grow = grow->link;
						}
						if (find == 1) break;
					}
					//printf("%s�� ��ȭ�� %s\n", cur->name, grow->name);



					if (cur->exp >= level_up) {
						cur->lv++;
						printf("+ �����մϴ�! %s�� ������ %d��/�� �Ǿ����ϴ�!\n", cur->name, cur->lv);
						int random;
						srand(time(NULL));
						random = rand() % 32;
						cur->stat.iv = random;
						cur->stat.lv_HP = (((cur->stat.HP * 2) + random) * cur->lv) / 100 + 10 + cur->lv;
						cur->stat.cur_HP = cur->stat.lv_HP;

						cur->exp = 0;
						int p_grow;
						srand(time(NULL));
						p_grow = rand() % 10;
						if (p_grow >= 0 && p_grow <= 3 && grow->link != NULL) {	
							if (grow->link != NULL) {
								grow = grow->link;
							}
							printf("\n+ .....\n");
							printf("+ .......... ����?\n");
							printf("+ %s �� ���°�........!\n", cur->name);
							printf("\n+ �����մϴ�! %s �� %s (��)�� ��ȭ�߽��ϴ�!\n", cur->name, grow->name);
							cur->dex_num = grow->dex_num;
							strcpy(cur->name, grow->name);
							strcpy(cur->type1, grow->type1);
							strcpy(cur->type2, grow->type2);
							cur->stat.HP = grow->stat.HP;
							cur->stat.Attack = grow->stat.Attack;
							cur->stat.Block = grow->stat.Block;
							cur->stat.Contact = grow->stat.Contact;
							cur->stat.Defence = grow->stat.Defence;
							cur->stat.Speed = grow->stat.Speed;
							int random;
							srand(time(NULL));
							random = rand() % 32;
							cur->stat.iv = random;
							cur->stat.lv_HP = (((cur->stat.HP * 2) + random) * cur->lv) / 100 + 10 + cur->lv;
							cur->stat.cur_HP = cur->stat.lv_HP;
							cur->dex_state = 2;
							grow->dex_state = 2;
						}						
					}
					flag = 1;
				}
			}
			else {
				cur->stat.cur_HP = 0;
				printf("+ %s�� %s���� %d�� ���ظ� ������!\n", adversary->name, cur->name, damage1);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				printf("+ %s �� ��������!\n", cur->name);
				flag = 1;

				//���� ���ϸ� ����  or ����ģ��
				if (user->num_poke > 1) {
					int choice;
					printf("   1. ���� ���ϸ��� ����Ѵ�.\n");
					printf("   2. ����ģ��.\n");
					printf("   >> ");
					scanf("%d", &choice);
					if (choice == 1) {
						//���� ���ϸ�
						cur = cur->link;
						int battle_order;
						while (1) {
							if (cur == NULL) break;
							printf("+ ������ �ұ�? > 1. �ο��.\n");
							printf("+              > 2. ���ϸ�.\n");
							printf("+              > 3. ��´�.\n");
							printf("+              > 4. ����ģ��.\n");
							printf("+              >> ");
							scanf("%d", &battle_order);
							int fight_result, run_result;
							if (battle_order == 1) {
								//�ο��
								//���� �տ�������, ü���� 0�� �ƴ� ���ϸ�
								POKE* my = cur;
								while (my != NULL) {
									if (my->stat.cur_HP != 0) {
										break;
									}
									my = my->link;
								}
								//printf("��Ʋ�� ���� ���ϸ�: %s\n", my->name);

								fight_result = Fight(adversary, user, my);
								if (fight_result == 1) break;
								else if (fight_result == 2) {
									//printf("�� �̻� ����� ���ϸ��� �����ϴ�.\n");
									break;
								}
							}

							else if (battle_order == 2) {
								//���ϸ�
								user_Pokemon(cur, user);
							}

							else if (battle_order == 3) {
								//��´�
								Catch(adversary, user, cur);
								if (adversary->stat.cur_HP == 0) break;
							}

							else if (battle_order == 4) {
								//����ģ��
								run_result = Run();
								if (run_result == 1) break;
							}
						}
					}
					else {
						//����
						int r;
						r = Run();
						if (r == 0) {
							//����ĥ �� ������
							while (1) {
								printf("   1. ���� ���ϸ��� ����Ѵ�.\n");
								printf("   2. ����ģ��.\n");
								printf("   >> ");
								scanf("%d", &choice);
								r = Run();
								if (choice == 1) {
									cur = cur->link;
									int battle_order;
									while (1) {
										if (cur == NULL) break;
										printf("+ ������ �ұ�? > 1. �ο��.\n");
										printf("+              > 2. ���ϸ�.\n");
										printf("+              > 3. ��´�.\n");
										printf("+              > 4. ����ģ��.\n");
										printf("+              >> ");
										scanf("%d", &battle_order);
										int fight_result, run_result;
										if (battle_order == 1) {
											//�ο��
											//���� �տ�������, ü���� 0�� �ƴ� ���ϸ�
											POKE* my = cur;
											while (my != NULL) {
												if (my->stat.cur_HP != 0) {
													break;
												}
												my = my->link;
											}
											//printf("��Ʋ�� ���� ���ϸ�: %s\n", my->name);

											fight_result = Fight(adversary, user, my);
											if (fight_result == 1) break;
											else if (fight_result == 2) {
												//printf("3 �� �̻� ����� ���ϸ��� �����ϴ�.\n");
												break;
											}
										}

										else if (battle_order == 2) {
											//���ϸ�
											user_Pokemon(cur, user);
										}

										else if (battle_order == 3) {
											//��´�
											Catch(adversary, user, cur);
											if (adversary->stat.cur_HP == 0) break;
										}

										else if (battle_order == 4) {
											//����ģ��
											run_result = Run();
											if (run_result == 1) break;
										}
									}
									break;
								}
								if (r == 1) {
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	else {
		//�� ���ϸ� ����
		if (adversary->stat.cur_HP > 0 && cur->stat.cur_HP > 0) {
			adversary->stat.cur_HP -= damage2;
			if (adversary->stat.cur_HP > 0) {
				printf("+ %s�� %s���� %d�� ���ظ� ������!\n", cur->name, adversary->name, damage2);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);

				cur->stat.cur_HP -= damage1;
				if (cur->stat.cur_HP > 0) {
					printf("+ %s�� %s���� %d�� ���ظ� ������!\n", adversary->name, cur->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				}
				else {
					cur->stat.cur_HP = 0;
					printf("+ %s�� %s���� %d�� ���ظ� ������!\n", adversary->name, cur->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
					printf("+ %s �� ��������!\n", cur->name);
					flag = 1;
					//���� ���ϸ� ���� or ����
					if (user->num_poke > 1) {
						int choice;
						printf("   1. ���� ���ϸ��� ����Ѵ�.\n");
						printf("   2. ����ģ��.\n");
						printf("   >> ");
						scanf("%d", &choice);
						if (choice == 1) {
							//���� ���ϸ�
							cur = cur->link;
							int battle_order;
							while (1) {
								if (cur == NULL) break;
								printf("+ ������ �ұ�? > 1. �ο��.\n");
								printf("+              > 2. ���ϸ�.\n");
								printf("+              > 3. ��´�.\n");
								printf("+              > 4. ����ģ��.\n");
								printf("+              >> ");
								scanf("%d", &battle_order);
								int fight_result, run_result;
								if (battle_order == 1) {
									//�ο��
									//���� �տ�������, ü���� 0�� �ƴ� ���ϸ�
									POKE* my = cur;
									while (my != NULL) {
										if (my->stat.cur_HP != 0) {
											break;
										}
										my = my->link;
									}
									//printf("��Ʋ�� ���� ���ϸ�: %s\n", my->name);

									fight_result = Fight(adversary, user, my);
									if (fight_result == 1) break;
									else if (fight_result == 2) {
										//printf("4 �� �̻� ����� ���ϸ��� �����ϴ�.\n");
										break;
									}
								}

								else if (battle_order == 2) {
									//���ϸ�
									user_Pokemon(cur, user);
								}

								else if (battle_order == 3) {
									//��´�
									Catch(adversary, user, cur);
									if (adversary->stat.cur_HP == 0) break;
								}

								else if (battle_order == 4) {
									//����ģ��
									run_result = Run();
									if (run_result == 1) break;
								}
							}
						}
						else {
							//����
							int r;
							r = Run();
							if (r == 0) {
								//����ĥ �� ������
								while (1) {
									printf("   1. ���� ���ϸ��� ����Ѵ�.\n");
									printf("   2. ����ģ��.\n");
									printf("   >> ");
									scanf("%d", &choice);
									r = Run();
									if (choice == 1) {
										cur = cur->link;
										int battle_order;
										while (1) {
											if (cur == NULL) break;
											printf("+ ������ �ұ�? > 1. �ο��.\n");
											printf("+              > 2. ���ϸ�.\n");
											printf("+              > 3. ��´�.\n");
											printf("+              > 4. ����ģ��.\n");
											printf("+              >> ");
											scanf("%d", &battle_order);
											int fight_result, run_result;
											if (battle_order == 1) {
												//�ο��
												//���� �տ�������, ü���� 0�� �ƴ� ���ϸ�
												POKE* my = cur;
												while (my != NULL) {
													if (my->stat.cur_HP != 0) {
														break;
													}
													my = my->link;
												}
												//printf("��Ʋ�� ���� ���ϸ�: %s\n", my->name);

												fight_result = Fight(adversary, user, my);
												if (fight_result == 1) break;
												else if (fight_result == 2) {
													//printf("3 �� �̻� ����� ���ϸ��� �����ϴ�.\n");
													break;
												}
											}

											else if (battle_order == 2) {
												//���ϸ�
												user_Pokemon(cur, user);
											}

											else if (battle_order == 3) {
												//��´�
												Catch(adversary, user, cur);
												if (adversary->stat.cur_HP == 0) break;
											}

											else if (battle_order == 4) {
												//����ģ��
												run_result = Run();
												if (run_result == 1) break;
											}
										}
										break;
									}
									if (r == 1) {
										break;
									}
								}
							}
						}
					}
				}
			}
			else {
				adversary->stat.cur_HP = 0;
				cur->exp += exp;
				printf("+ %s�� %s���� %d�� ���ظ� ������!\n", cur->name, adversary->name, damage2);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				printf("+ %s�� ����Ʈ�ȴ�!\n", adversary->name);
				printf("+ %s�� %d��ŭ�� ����ġ�� �����!\n", cur->name, exp);
				//printf("+ %s�� ���� ����ġ: %d\n", cur->name, cur->exp);
				flag = 1;

				
				int find = 0;
				POKE* grow = (POKE*)malloc(sizeof(POKE));
				for (int i = 0; i < 78; i++) {
					grow = head[i];
					while (grow != NULL) {
						if (grow->dex_num == cur->dex_num) {
							//printf("ã�Ҵ� %s!\n", grow->name);
							find = 1;
							break;
						}
						grow = grow->link;
					}
					if (find == 1) break;
				}
				
				//printf("%s�� ��ȭ�� %s\n", cur->name, grow->name);



				if (cur->exp >= level_up) {
					cur->lv++;
					printf("+ �����մϴ�! %s�� ������ %d��/�� �Ǿ����ϴ�!\n", cur->name, cur->lv);
					cur->exp = 0;
					int random;
					srand(time(NULL));
					random = rand() % 32;
					cur->stat.iv = random;
					cur->stat.lv_HP = (((cur->stat.HP * 2) + random) * cur->lv) / 100 + 10 + cur->lv;
					cur->stat.cur_HP = cur->stat.lv_HP;

					int p_grow;
					srand(time(NULL));
					p_grow = rand() % 10;
					if (p_grow >= 0 && p_grow <= 3&&grow->link!=NULL) {
						if (grow->link != NULL) {
							grow = grow->link;
						}
						printf("\n+ .....\n");
						printf("+ .......... ����?\n");
						printf("+ %s �� ���°�........!\n", cur->name);
						printf("\n+ �����մϴ�! %s �� %s (��)�� ��ȭ�߽��ϴ�!\n", cur->name, grow->name);
						cur->dex_num = grow->dex_num;
						strcpy(cur->name, grow->name);
						strcpy(cur->type1, grow->type1);
						strcpy(cur->type2, grow->type2);
						cur->stat.HP = grow->stat.HP;
						cur->stat.Attack = grow->stat.Attack;
						cur->stat.Block = grow->stat.Block;
						cur->stat.Contact = grow->stat.Contact;
						cur->stat.Defence = grow->stat.Defence;
						cur->stat.Speed = grow->stat.Speed;
						int random;
						srand(time(NULL));
						random = rand() % 32;
						cur->stat.iv = random;
						cur->stat.lv_HP = (((cur->stat.HP * 2) + random) * cur->lv) / 100 + 10 + cur->lv;
						cur->stat.cur_HP = cur->stat.lv_HP;
						cur->dex_state = 2;
						grow->dex_state = 2;
					}
				}
			}
		}
	}
	POKE* curr;
	curr = user->poke;
	int die = 0;
	while (curr != NULL) {
		if (curr->stat.cur_HP == 0) {
			die++;
		}
		curr = curr->link;
	}
	//printf("���ϸ� �� %d���� ����\n", die);
	if (die == user->num_poke) flag = 2;
	//printf("������ ���ϸ��� �� %d����\n", user->num_poke);
	//printf("�� ���ϸ��� ���� HP: %d\n", cur->stat.cur_HP);
	if (user->num_poke == 1 && cur->stat.cur_HP == 0) flag = 2;
	return flag;
}



void user_Pokemon(POKE* poke, User* user) {
	//���� ����ڰ� ���� ���ϸ���� �����ְ�, ���¸� ���ų� ������ �ٲ۴�
	printf("+---------[%s]�� ���ϸ�---------+\n", user->user_name);
	POKE* curr = user->poke;
	int a = 1;
	while (1) {
		printf(" %d. %s\n", a++, curr->name);
		if (curr->link == NULL) break;
		curr = curr->link;
	}
	int order;
	printf("\n");
	printf("+ 1. ���¸� ����.		+\n");
	printf("+ 2. ������ �ٲ۴�.		+\n");
	printf("+ 3. ����.			+\n");
	printf("+ >> ");
	scanf("%d", &order);
	if (order == 1) {
		//���¸� ����
		POKE* show = user->poke;
		int b = 1;
		while (1) {
			printf("+ %d. %s\n", b++, show->name);
			if (show->type2[0] != '0') {
				printf("    Type =(%s, %s)\n", show->type1, show->type2);
			}
			else {
				printf("    Type = (%s)\n", show->type1);
			}
			printf("    HP = %d / %d\n", show->stat.cur_HP, show->stat.lv_HP);
			printf("    ���� = %d\n", show->stat.Attack);
			printf("    ��� = %d\n", show->stat.Block);
			printf("    Ư������ = %d\n", show->stat.Contact);
			printf("    Ư������ = %d\n", show->stat.Defence);
			printf("    ���ǵ� = %d\n\n", show->stat.Speed);
			if (show->link == NULL) break;
			show = show->link;
		}
		printf("+---------[%s]�� ���ϸ�---------+\n", user->user_name);
		curr = user->poke;
		a = 1;
		while (1) {
			printf(" %d. %s\n", a, curr->name);
			if (curr->link == NULL) break;
			a++;
			curr = curr->link;
		}
	}
	else if (order == 2) {
		//������ �ٲ۴�
		POKE* change = user->poke;
		int c = 1;
		while (1) {
			if (change->type2[0] != '0') {
				printf("+ %d. %s (Type1 : %s, Type2 : %s)\n", c, change->name, change->type1, change->type2);
			}
			else {
				printf("+ %d. %s (Type : %s)\n", c, change->name, change->type1);
			}
			c++;
			if (change->link == NULL) break;
			change = change->link;
		}
		int p1, p2;
		printf("+  ������ �ٲ� ���ϸ��� �����ϼ���.\n");
		printf("+ >> ");
		scanf("%d %d", &p1, &p2);
		//���� �ٲٰ� �� ���
		//memcpy(newpoke, adversary, sizeof(POKE));
		POKE* P1, * P2;
		P1 = user->poke;
		P2 = user->poke;
		for (int i = 0; i < p1-1; i++) {
			P1 = P1->link;
		}
		for (int i = 0; i < p2-1; i++) {
			P2 = P2->link;
		}
		POKE* temp=(POKE*)malloc(sizeof(POKE));
		memcpy(temp, P1, sizeof(POKE));
		memcpy(P1, P2, sizeof(POKE));
		memcpy(P2, temp, sizeof(POKE));
		POKE* l1, * l2;
		l1 = P2->link;
		l2 = P1->link;
		P1->link = l1;
		P2->link = l2;
		printf("+---------[%s]�� ���ϸ�---------+\n", user->user_name);
		curr = user->poke;
		a = 1;
		while (1) {
			printf(" %d. %s\n", a, curr->name);
			if (curr->link == NULL) break;
			a++;
			curr = curr->link;
		}
	}
	else {
		//����
	}
}

void Catch(POKE* adversary, User* user, POKE* poke) {
	//�߻� ���ϸ� ��ȹ
	int random;
	srand(time(NULL));
	random = rand() % 2;
	if (random == 1) {
		//��´�
		printf("+ �ų���~! %s�� ��Ҵ�!\n", adversary->name);
		user->num_poke++;
		POKE* newpoke=(POKE*)malloc(sizeof(POKE));
		memcpy(newpoke, adversary, sizeof(POKE));
		newpoke->dex_state = 2;
		newpoke->link = NULL;
		POKE *curr;
		curr = poke;
		while (1) {
			if (curr->link == NULL) break;
			curr = curr->link;
		}
		curr->link = newpoke;
		curr = curr->link;
		adversary->stat.cur_HP = 0;
		//head�� �ش� ���ϸ� dex_state=2
		int i = 0;
		POKE* dex = head[i];
		dex = dex->link;
		while (1) {
			if (dex->dex_num == curr->dex_num) {
				dex->dex_state = 2;
				break;
			}
			dex = dex->link;
			if (dex == NULL) {
				i++;
				dex = head[i];
			}
		}
	}
	else if (random == 0) {
		//��ģ��
		printf("+ �ƽ���! ���ݸ� �� �ϸ� ���� �� �־��µ�!\n");
	}
}

int Run() {
	//���� ����->����, ����->�ٽ� ��Ʋ
	int random;
	srand(time(NULL));
	random = rand() % 10;
	if (random >= 0 && random <= 1) {
		//����
		printf("+ ������ �����ƴ�!\n");
		return 1;
	}
	else {
		//���� ����
		printf("+ ����ĥ �� ������!\n");
		return 0;
	}
}

void Pokedex() {
	//���ϸ� ���� ��Ȳ ���
	for (int i = 0; i < 78; i++) {
		PrintAll(head[i]);
	}
}

void Pokecen(User* user) {
	//���ϸ� ȸ��
	POKE* curr = user->poke;
	for (int i = 0; i < user->num_poke; i++) {
		curr->stat.cur_HP = curr->stat.lv_HP;
		curr = curr->link;
	}
	printf("\n+ ���ϸ��� HP�� ��� ȸ���Ǿ����ϴ�! +\n\n");
}

//head�� ���ϸ� ��ȭ�� �����ϱ�
void fill_head(POKE** head) {
	int dexnum=0, hp=0, att=0, def=0, s_att=0, s_def=0, speed=0;
	char p_name[20] = {0}, type[60] = {0};
	int index = 0;
	FILE* fp = fopen("sogang_poke.txt", "r");
	fscanf(fp, "%d %s %s %d %d %d %d %d %d", &dexnum, p_name, type, &hp, &att, &def, &s_att, &s_def, &speed);
	while (!feof(fp)) {
		//printf("%d %s %s %d %d %d %d %d %d\n", dexnum, p_name, type, hp, att, def, s_att, s_def, speed);
		//fscanf(fp, "%d %s %s %d %d %d %d %d %d", &dexnum, p_name, type, &hp, &att, &def, &s_att, &s_def, &speed);
		
		//������ �ʹ� �����ϱ� newnode ����ü�� ��Ƽ� �Լ��� parameter�� ������
		POKE* newnode = (POKE*)malloc(sizeof(POKE));

		newnode->link = NULL;
		newnode->dex_num = dexnum;
		newnode->dex_state = 0;
		strcpy(newnode->name, p_name);
		
		char* pch = strtok(type, ",");
		strcpy(newnode->type1, pch);
		pch = strtok(NULL, ",");
		if (pch != NULL) {
			strcpy(newnode->type2, pch);
		}
		else {
			//*newnode->type2 = NULL;
			newnode->type2[0] = '0';
		}
		newnode->exp = 0;
		(newnode->stat).HP = hp;
		(newnode->stat).Attack = att;
		(newnode->stat).Block = def;
		(newnode->stat).Contact = s_att;
		(newnode->stat).Defence = s_def;
		(newnode->stat).Speed = speed;

		//head[index] ����Ʈ���� ������ ��� ���ؼ� node�� ����
		POKE* node = (POKE*)malloc(sizeof(POKE));
		node = head[index];
		while (1) {
			if (node->link == NULL) break;
			node = node->link;
		}
		
		//������ȣ�� ���� node�� newnode �����ϱ�
		if (dexnum >= 1 && dexnum <= 18) {
			if (dexnum % 3 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 2) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				//������ ��ȭ�� �������� head[index]�� index���� 1����=>���� ���ϸ�
				index++;
			}
		}

		else if (dexnum >= 19 && dexnum <= 28) {
			if (dexnum % 2 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 29 && dexnum <= 34) {
			if (dexnum % 3 == 2) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 35 && dexnum <= 42) {
			if (dexnum % 2 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 43 && dexnum <= 45) {
			if (dexnum % 3 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 2) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 46 && dexnum <= 59) {
			if (dexnum % 2 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 60 && dexnum <= 71) {
			if (dexnum % 3 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 72 && dexnum <= 73) {
			if (dexnum % 2 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 74 && dexnum <= 76) {
			if (dexnum % 3 == 2) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 77 && dexnum <= 82) {
			if (dexnum % 2 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum == 83) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 84 && dexnum <= 91) {
			if (dexnum % 2 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 92 && dexnum <= 94) {
			if (dexnum % 3 == 2) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum == 95) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 96 && dexnum <= 107) {
			if (dexnum % 2 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum == 108) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 109 && dexnum <= 112) {
			if (dexnum % 2 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 113 && dexnum <= 115) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 116 && dexnum <= 121) {
			if (dexnum % 2 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 122 && dexnum <= 128) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 129 && dexnum <= 130) {
			if (dexnum % 2 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 131 && dexnum <= 132) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 133 && dexnum <= 136) {
			if (dexnum % 4 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 4 == 2) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 4 == 3) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum == 137) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 138 && dexnum <= 141) {
			if (dexnum % 2 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 142 && dexnum <= 146) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}

		else if (dexnum >= 147 && dexnum <= 149) {
			if (dexnum % 3 == 0) {
				combine_node(node, newnode);
				node = node->link;
			}
			else if (dexnum % 3 == 1) {
				combine_node(node, newnode);
				node = node->link;
			}
			else {
				combine_node(node, newnode);
				node = node->link;
				//printf("index: %d\n", index);
				//PrintAll(head[index]);
				index++;
			}
		}

		else if (dexnum >= 150 && dexnum <= 151) {
			combine_node(node, newnode);
			node = node->link;
			//printf("index: %d\n", index);
			//PrintAll(head[index]);
			index++;
		}
		fscanf(fp, "%d %s %s %d %d %d %d %d %d", &dexnum, p_name, type, &hp, &att, &def, &s_att, &s_def, &speed);
	}
	fclose(fp);
}

void combine_node(POKE* node, POKE* newnode) {
	node->link = newnode;
	newnode->link = NULL;
}

void PrintAll(POKE* head) {
	POKE* curr = head;
	curr = curr->link;
	while (curr->link != NULL) {
		//printf("%d %s %s %s\n", curr->dex_num, curr->name, curr->type1, curr->type2);
		if (curr->dex_state == 0) {
			printf("%d. ???\n", curr->dex_num);
		}
		else if (curr->dex_state == 1) {
			printf("%d. %s (Type : ???)\n", curr->dex_num, curr->name);
		}
		else {
			if (curr->type2[0] != '0') {
				printf("%d. %s (Type : %s, %s)\n", curr->dex_num, curr->name, curr->type1, curr->type2);
			}
			else {
				printf("%d. %s (Type : %s)\n", curr->dex_num, curr->name, curr->type1);
			}
		}
		curr = curr->link;
	}
	//printf("%d %s %s %s\n", curr->dex_num, curr->name, curr->type1, curr->type2);
	if (curr->dex_state == 0) {
		printf("%d. ???\n", curr->dex_num);
	}
	else if (curr->dex_state == 1) {
		printf("%d. %s (Type : ???)\n", curr->dex_num, curr->name);
	}
	else {
		if (curr->type2[0] != '0') {
			printf("%d. %s (Type : %s, %s)\n", curr->dex_num, curr->name, curr->type1, curr->type2);
		}
		else {
			printf("%d. %s (Type : %s)\n", curr->dex_num, curr->name, curr->type1);
		}
	}
}