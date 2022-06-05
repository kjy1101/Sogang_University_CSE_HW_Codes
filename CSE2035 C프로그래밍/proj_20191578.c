#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct {
	int lv_HP; //현재 레벨에서의 체력
	int cur_HP; //현재 상태에서의 체력
	int HP; //체력
	int Attack; //공격
	int Block; //방어
	int Contact; //특수공격
	int Defence; //특수방어
	int Speed; //스피드
	int iv; //랜덤 값(0~31)
} Stat;

typedef struct {
	int lv; //레벨
	int dex_num; //도감 번호
	char name[20]; //포켓몬 이름
	char type1[30]; //타입1
	char type2[30]; //타입2
	int dex_state; //0->도감에 등록되지 않음, 1->발견함, 2->잡았다
	int exp; //경험치
	Stat stat; //스탯
	struct POKE* link;
} POKE;

typedef struct {
	char user_name[10]; //사용자 이름
	POKE* poke; //사용자가 지닌 포켓몬(최대 6마리)
	int num_poke; //사용자가 현재 지닌 포켓몬의 수
} User;

POKE** head; //모든 포켓몬의 진화 과정을 저장
POKE* box; //포켓몬 박스

void fill_head(POKE** head); //head에 모든 포켓몬의 진화 과정을 저장하는 함수
void combine_node(POKE*, POKE*); //node1 뒤에 node2를 붙이는 함수
void PrintAll(POKE*); //출력함수

void Battle(User* user); //포켓몬 배틀
int Fight(POKE* adversary, User* user, POKE* cur);
	//adversary: 랜덤으로 등장한 야생 포켓몬
	//cur: user의 현재 포켓몬
	//배틀 상황 return
void Catch(POKE* adversary, User* user, POKE* curr); //야생포켓몬 adversary를 포획
int Run(); //도망칠 수 있으면 종료, 없으면 배틀 계속


void Pokedex(); //포켓몬 도감 현황 출력
void user_Pokemon(POKE* poke, User* user); //user가 지닌 포켓몬들 관리
void Report(User* user); //사용자의 정보 출력(리포트)
void Pokecen(User* user); //포켓몬 체력 회복

int main(void) {
	//head안에 도감 정보 채우기
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

	//게임 시작
	User *user=(User*)malloc(sizeof(User));
	user->poke = (POKE*)malloc(6 * sizeof(POKE));
	user->num_poke = 0;
	int order, starting;
	int next;
	printf("+----------Pokemon R&AS----------+\n");
	printf("+  메뉴를 선택해주세요.          +\n");
	printf("+  1. 새로 시작한다.             +\n");
	printf("+  2. 종료.                      +\n\n");
	printf("+  >> ");
	scanf("%d", &order);
	if (order == 1) {
		printf("\n+------------New Game------------+\n");
		printf("+ 당신의 이름을 입력해주세요.    +\n");
		printf("+ >> ");
		scanf("%s", &(user->user_name));
		printf("\n+ 스타팅 포켓몬을 선택해주세요.  +\n");
		printf("+--------------------------------+\n");
		printf("+ 1. Bulbasaur (Type1 : Grass, Type2 : Poison)\n");
		printf("+ 2. Charmander (Type : Fire)\n");
		printf("+ 3. Squirtle (Type : Water)\n");
		printf("+--------------------------------+\n");
		printf("+ >> ");
		scanf("%d", &starting);
		starting--;
		user->num_poke++;

		//user의 첫번째 포켓몬 정보 옮기기
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
		//		printf("랜덤수는 %d(으)로 나왔다.\n", random);
//		printf("스타팅 포켓몬의 HP는 는 %d(이)다.\n", (user->poke[0]).stat.lv_HP);
//		printf("스타팅 포켓몬의 레벨은 %d(이)다.\n", (user->poke[0]).lv);
		Report(user);
		while (1) {
			printf("+-----------Main Menu------------+\n");
			printf("+ 메뉴를 선택해주세요.           +\n");
			printf("+ 1. 배틀.                       +\n");
			printf("+ 2. 도감.                       +\n");
			printf("+ 3. 지닌 포켓몬.                +\n");
			printf("+ 4. 포켓몬 센터.                +\n");
			printf("+ 5. 리포트.                     +\n");
			printf("+ 6. 종료.                       +\n");
			printf("+ >> ");
			scanf("%d", &next);
			if (next == 1) {
				//배틀
				Battle(user);
			}

			else if (next == 2) {
				//도감(포켓몬 도감 현황 출력)
				Pokedex();
			}

			else if (next == 3) {
				//지닌 포켓몬(관리)
				user_Pokemon(user->poke, user);
			}

			else if (next == 4) {
				//포켓몬 센터(포켓몬 회복, 박스 조작)
				Pokecen(user);
			}

			else if (next == 5) {
				//리포트
				Report(user);
			}

			else if (next == 6) {
				//종료
				break;
			}
		}
	}
	else {
		//게임 종료
	}
	
	return 0;
}

void Report(User* user) {
	FILE* fp;
	fp = fopen("log.txt", "w");
	//파일에 출력
	fprintf(fp, "+--------------Report--------------+\n");
	fprintf(fp, "+ 현재까지의 정보를 기록합니다.  +\n");
	fprintf(fp, "+ 트레이너 명 = [%s]\n", user->user_name);
	fprintf(fp, "+ 지닌 포켓몬 = \n");
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

	//콘솔창 출력
	printf("+-------------Report-------------+\n");
	printf("+ 현재까지의 정보를 기록합니다.  +\n");
	printf("+ 트레이너 명 = [%s]\n", user->user_name);
	printf("+ 지닌 포켓몬 = \n");
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
	//배틀
	//등장할 야생 포켓몬 정의하기
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
//	printf("야생의 포켓몬 도감번호: %d\n", random + 1);
//	printf("야생의 포켓몬 레벨은 당신의 포켓몬과 %d만큼 차이난다.\n", lv_random);
	POKE* curr = head[i];
	curr = curr->link;
	while (1) {
		if (curr->dex_num == random + 1) {
			adversary = curr;
			adversary->dex_state = 1;
			curr->dex_state = 1; //발견했다!
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


	//배틀 시작
	printf("+-----------Battle-----------+\n");
	printf("+ 앗! 야생의 %s(Lv.%d)가 나타났다!\n", adversary->name, adversary->lv);
	while (1) {
		printf("+ 무엇을 할까? > 1. 싸운다.\n");
		printf("+              > 2. 포켓몬.\n");
		printf("+              > 3. 잡는다.\n");
		printf("+              > 4. 도망친다.\n");
		printf("+              >> ");
		scanf("%d", &battle_order);
		int fight_result, run_result;
		if (battle_order == 1) {
			//싸운다
			//가장 앞에서부터, 체력이 0이 아닌 포켓몬
			POKE* my = user->poke;
			while (my != NULL) {
				if (my->stat.cur_HP != 0) {
					break;
				}
				my = my->link;
			}
			//printf("배틀에 나갈 포켓몬: %s\n", my->name);

			fight_result = Fight(adversary, user, my);
			if (fight_result == 1) break;
			else if (fight_result == 2) {
				printf("더 이상 사용할 포켓몬이 없습니다.\n");
				break;
			}
		}

		else if (battle_order == 2) {
			//포켓몬
			user_Pokemon(user->poke, user);
		}

		else if (battle_order == 3) {
			//잡는다
			Catch(adversary, user, user->poke);
			if (adversary->stat.cur_HP == 0) break;
		}

		else if (battle_order == 4) {
			//도망친다
			run_result = Run();
			if (run_result == 1) {
				break;
			}
		}
	}
}



int Fight(POKE* adversary, User* user, POKE* cur) {
	//adversary(야생포켓몬)과 cur(내 포켓몬)의 배틀

	//상대에게 입힐 수 있는 피해량 damage
	int damage1, damage2; //damage1은 야생포켓몬이 나한테, damage2는 내가 야생포켓몬한테
	int p, random;
	srand(time(NULL));
	p = rand() % 2; //p=0이면 공격, p=1이면 특수공격
	random = rand() % 5;
	if (p == 0) {
		//그냥 공격, 그냥 방어
		damage1 = ((((adversary->lv * 2) / 5 + 2) * adversary->stat.Attack) / cur->stat.Block / 50 + 2) + random;
		damage2 = ((((cur->lv * 2) / 5 + 2) * cur->stat.Attack) / adversary->stat.Block / 50 + 2) + random;
	}
	else {
		//특수 공격, 특수 방어
		damage1 = ((((adversary->lv * 2) / 5 + 2) * adversary->stat.Contact) / cur->stat.Defence / 50 + 2) + random;
		damage2 = ((((cur->lv * 2) / 5 + 2) * cur->stat.Contact) / adversary->stat.Defence / 50 + 2) + random;
	}
	//야생포켓몬을 쓰러트리면 얻을 경험치
	int exp;
	exp = (adversary->lv * adversary->stat.HP) / 5;
	int level_up;
	level_up = cur->lv * cur->lv * cur->lv;

	int flag = 0; //배틀 종료시 flag=1, flag=2이면 포켓몬이 다 죽은거
	//공격시작!!!!!!!!

	if (adversary->stat.Speed >= cur->stat.Speed) {
		//야생 포켓몬 선공
		if (adversary->stat.cur_HP > 0 && cur->stat.cur_HP > 0) {
			cur->stat.cur_HP -= damage1;
			if (cur->stat.cur_HP > 0) {
				printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", adversary->name, cur->name, damage1);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
			
				adversary->stat.cur_HP -= damage2;
				if (adversary->stat.cur_HP > 0) {
					printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", cur->name, adversary->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				}
				else {
					adversary->stat.cur_HP = 0;
					cur->exp += exp;
					printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", cur->name, adversary->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
					printf("+ %s를 쓰러트렸다!\n", adversary->name);
					printf("+ %s는 %d만큼의 경험치를 얻었다!\n", cur->name, exp);
					//printf("+ %s의 현재 경험치: %d\n", cur->name, cur->exp);

					int find = 0;
					POKE* grow = (POKE*)malloc(sizeof(POKE));
					for (int i = 0; i < 78; i++) {
						grow = head[i];
						while (grow != NULL) {
							if (grow->dex_num == cur->dex_num) {
								//printf("찾았다 %s!\n", grow->name);
								find = 1;
								break;
							}
							grow = grow->link;
						}
						if (find == 1) break;
					}
					//printf("%s의 진화형 %s\n", cur->name, grow->name);



					if (cur->exp >= level_up) {
						cur->lv++;
						printf("+ 축하합니다! %s의 레벨이 %d이/가 되었습니다!\n", cur->name, cur->lv);
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
							printf("+ .......... 오잉?\n");
							printf("+ %s 의 상태가........!\n", cur->name);
							printf("\n+ 축하합니다! %s 는 %s (으)로 진화했습니다!\n", cur->name, grow->name);
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
				printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", adversary->name, cur->name, damage1);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				printf("+ %s 는 쓰러졌다!\n", cur->name);
				flag = 1;

				//다음 포켓몬 선택  or 도망친다
				if (user->num_poke > 1) {
					int choice;
					printf("   1. 다음 포켓몬을 사용한다.\n");
					printf("   2. 도망친다.\n");
					printf("   >> ");
					scanf("%d", &choice);
					if (choice == 1) {
						//다음 포켓몬
						cur = cur->link;
						int battle_order;
						while (1) {
							if (cur == NULL) break;
							printf("+ 무엇을 할까? > 1. 싸운다.\n");
							printf("+              > 2. 포켓몬.\n");
							printf("+              > 3. 잡는다.\n");
							printf("+              > 4. 도망친다.\n");
							printf("+              >> ");
							scanf("%d", &battle_order);
							int fight_result, run_result;
							if (battle_order == 1) {
								//싸운다
								//가장 앞에서부터, 체력이 0이 아닌 포켓몬
								POKE* my = cur;
								while (my != NULL) {
									if (my->stat.cur_HP != 0) {
										break;
									}
									my = my->link;
								}
								//printf("배틀에 나갈 포켓몬: %s\n", my->name);

								fight_result = Fight(adversary, user, my);
								if (fight_result == 1) break;
								else if (fight_result == 2) {
									//printf("더 이상 사용할 포켓몬이 없습니다.\n");
									break;
								}
							}

							else if (battle_order == 2) {
								//포켓몬
								user_Pokemon(cur, user);
							}

							else if (battle_order == 3) {
								//잡는다
								Catch(adversary, user, cur);
								if (adversary->stat.cur_HP == 0) break;
							}

							else if (battle_order == 4) {
								//도망친다
								run_result = Run();
								if (run_result == 1) break;
							}
						}
					}
					else {
						//도망
						int r;
						r = Run();
						if (r == 0) {
							//도망칠 수 없었다
							while (1) {
								printf("   1. 다음 포켓몬을 사용한다.\n");
								printf("   2. 도망친다.\n");
								printf("   >> ");
								scanf("%d", &choice);
								r = Run();
								if (choice == 1) {
									cur = cur->link;
									int battle_order;
									while (1) {
										if (cur == NULL) break;
										printf("+ 무엇을 할까? > 1. 싸운다.\n");
										printf("+              > 2. 포켓몬.\n");
										printf("+              > 3. 잡는다.\n");
										printf("+              > 4. 도망친다.\n");
										printf("+              >> ");
										scanf("%d", &battle_order);
										int fight_result, run_result;
										if (battle_order == 1) {
											//싸운다
											//가장 앞에서부터, 체력이 0이 아닌 포켓몬
											POKE* my = cur;
											while (my != NULL) {
												if (my->stat.cur_HP != 0) {
													break;
												}
												my = my->link;
											}
											//printf("배틀에 나갈 포켓몬: %s\n", my->name);

											fight_result = Fight(adversary, user, my);
											if (fight_result == 1) break;
											else if (fight_result == 2) {
												//printf("3 더 이상 사용할 포켓몬이 없습니다.\n");
												break;
											}
										}

										else if (battle_order == 2) {
											//포켓몬
											user_Pokemon(cur, user);
										}

										else if (battle_order == 3) {
											//잡는다
											Catch(adversary, user, cur);
											if (adversary->stat.cur_HP == 0) break;
										}

										else if (battle_order == 4) {
											//도망친다
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
		//내 포켓몬 선공
		if (adversary->stat.cur_HP > 0 && cur->stat.cur_HP > 0) {
			adversary->stat.cur_HP -= damage2;
			if (adversary->stat.cur_HP > 0) {
				printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", cur->name, adversary->name, damage2);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);

				cur->stat.cur_HP -= damage1;
				if (cur->stat.cur_HP > 0) {
					printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", adversary->name, cur->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				}
				else {
					cur->stat.cur_HP = 0;
					printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", adversary->name, cur->name, damage2);
					printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
					printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
					printf("+ %s 는 쓰러졌다!\n", cur->name);
					flag = 1;
					//다음 포켓몬 선택 or 도망
					if (user->num_poke > 1) {
						int choice;
						printf("   1. 다음 포켓몬을 사용한다.\n");
						printf("   2. 도망친다.\n");
						printf("   >> ");
						scanf("%d", &choice);
						if (choice == 1) {
							//다음 포켓몬
							cur = cur->link;
							int battle_order;
							while (1) {
								if (cur == NULL) break;
								printf("+ 무엇을 할까? > 1. 싸운다.\n");
								printf("+              > 2. 포켓몬.\n");
								printf("+              > 3. 잡는다.\n");
								printf("+              > 4. 도망친다.\n");
								printf("+              >> ");
								scanf("%d", &battle_order);
								int fight_result, run_result;
								if (battle_order == 1) {
									//싸운다
									//가장 앞에서부터, 체력이 0이 아닌 포켓몬
									POKE* my = cur;
									while (my != NULL) {
										if (my->stat.cur_HP != 0) {
											break;
										}
										my = my->link;
									}
									//printf("배틀에 나갈 포켓몬: %s\n", my->name);

									fight_result = Fight(adversary, user, my);
									if (fight_result == 1) break;
									else if (fight_result == 2) {
										//printf("4 더 이상 사용할 포켓몬이 없습니다.\n");
										break;
									}
								}

								else if (battle_order == 2) {
									//포켓몬
									user_Pokemon(cur, user);
								}

								else if (battle_order == 3) {
									//잡는다
									Catch(adversary, user, cur);
									if (adversary->stat.cur_HP == 0) break;
								}

								else if (battle_order == 4) {
									//도망친다
									run_result = Run();
									if (run_result == 1) break;
								}
							}
						}
						else {
							//도망
							int r;
							r = Run();
							if (r == 0) {
								//도망칠 수 없었다
								while (1) {
									printf("   1. 다음 포켓몬을 사용한다.\n");
									printf("   2. 도망친다.\n");
									printf("   >> ");
									scanf("%d", &choice);
									r = Run();
									if (choice == 1) {
										cur = cur->link;
										int battle_order;
										while (1) {
											if (cur == NULL) break;
											printf("+ 무엇을 할까? > 1. 싸운다.\n");
											printf("+              > 2. 포켓몬.\n");
											printf("+              > 3. 잡는다.\n");
											printf("+              > 4. 도망친다.\n");
											printf("+              >> ");
											scanf("%d", &battle_order);
											int fight_result, run_result;
											if (battle_order == 1) {
												//싸운다
												//가장 앞에서부터, 체력이 0이 아닌 포켓몬
												POKE* my = cur;
												while (my != NULL) {
													if (my->stat.cur_HP != 0) {
														break;
													}
													my = my->link;
												}
												//printf("배틀에 나갈 포켓몬: %s\n", my->name);

												fight_result = Fight(adversary, user, my);
												if (fight_result == 1) break;
												else if (fight_result == 2) {
													//printf("3 더 이상 사용할 포켓몬이 없습니다.\n");
													break;
												}
											}

											else if (battle_order == 2) {
												//포켓몬
												user_Pokemon(cur, user);
											}

											else if (battle_order == 3) {
												//잡는다
												Catch(adversary, user, cur);
												if (adversary->stat.cur_HP == 0) break;
											}

											else if (battle_order == 4) {
												//도망친다
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
				printf("+ %s는 %s에게 %d의 피해를 입혔다!\n", cur->name, adversary->name, damage2);
				printf("+ %s(lv.%d)		%s(lv.%d)\n", cur->name, cur->lv, adversary->name, adversary->lv);
				printf("+ HP = (%d/%d)			(%d/%d)\n\n", cur->stat.cur_HP, cur->stat.lv_HP, adversary->stat.cur_HP, adversary->stat.lv_HP);
				printf("+ %s를 쓰러트렸다!\n", adversary->name);
				printf("+ %s는 %d만큼의 경험치를 얻었다!\n", cur->name, exp);
				//printf("+ %s의 현재 경험치: %d\n", cur->name, cur->exp);
				flag = 1;

				
				int find = 0;
				POKE* grow = (POKE*)malloc(sizeof(POKE));
				for (int i = 0; i < 78; i++) {
					grow = head[i];
					while (grow != NULL) {
						if (grow->dex_num == cur->dex_num) {
							//printf("찾았다 %s!\n", grow->name);
							find = 1;
							break;
						}
						grow = grow->link;
					}
					if (find == 1) break;
				}
				
				//printf("%s의 진화형 %s\n", cur->name, grow->name);



				if (cur->exp >= level_up) {
					cur->lv++;
					printf("+ 축하합니다! %s의 레벨이 %d이/가 되었습니다!\n", cur->name, cur->lv);
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
						printf("+ .......... 오잉?\n");
						printf("+ %s 의 상태가........!\n", cur->name);
						printf("\n+ 축하합니다! %s 는 %s (으)로 진화했습니다!\n", cur->name, grow->name);
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
	//printf("포켓몬 총 %d마리 죽음\n", die);
	if (die == user->num_poke) flag = 2;
	//printf("유저의 포켓몬은 총 %d마리\n", user->num_poke);
	//printf("그 포켓몬의 현재 HP: %d\n", cur->stat.cur_HP);
	if (user->num_poke == 1 && cur->stat.cur_HP == 0) flag = 2;
	return flag;
}



void user_Pokemon(POKE* poke, User* user) {
	//현재 사용자가 지닌 포켓몬들을 보여주고, 상태를 보거나 순서를 바꾼다
	printf("+---------[%s]의 포켓몬---------+\n", user->user_name);
	POKE* curr = user->poke;
	int a = 1;
	while (1) {
		printf(" %d. %s\n", a++, curr->name);
		if (curr->link == NULL) break;
		curr = curr->link;
	}
	int order;
	printf("\n");
	printf("+ 1. 상태를 본다.		+\n");
	printf("+ 2. 순서를 바꾼다.		+\n");
	printf("+ 3. 종료.			+\n");
	printf("+ >> ");
	scanf("%d", &order);
	if (order == 1) {
		//상태를 본다
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
			printf("    공격 = %d\n", show->stat.Attack);
			printf("    방어 = %d\n", show->stat.Block);
			printf("    특수공격 = %d\n", show->stat.Contact);
			printf("    특수공격 = %d\n", show->stat.Defence);
			printf("    스피드 = %d\n\n", show->stat.Speed);
			if (show->link == NULL) break;
			show = show->link;
		}
		printf("+---------[%s]의 포켓몬---------+\n", user->user_name);
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
		//순서를 바꾼다
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
		printf("+  순서를 바꿀 포켓몬을 선택하세요.\n");
		printf("+ >> ");
		scanf("%d %d", &p1, &p2);
		//순서 바꾸고 또 출력
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
		printf("+---------[%s]의 포켓몬---------+\n", user->user_name);
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
		//종료
	}
}

void Catch(POKE* adversary, User* user, POKE* poke) {
	//야생 포켓몬 포획
	int random;
	srand(time(NULL));
	random = rand() % 2;
	if (random == 1) {
		//잡는다
		printf("+ 신난다~! %s를 잡았다!\n", adversary->name);
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
		//head에 해당 포켓몬 dex_state=2
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
		//놓친다
		printf("+ 아쉽다! 조금만 더 하면 잡을 수 있었는데!\n");
	}
}

int Run() {
	//도망 성공->종료, 실패->다시 배틀
	int random;
	srand(time(NULL));
	random = rand() % 10;
	if (random >= 0 && random <= 1) {
		//도망
		printf("+ 무사히 도망쳤다!\n");
		return 1;
	}
	else {
		//도망 실패
		printf("+ 도망칠 수 없었다!\n");
		return 0;
	}
}

void Pokedex() {
	//포켓몬 도감 현황 출력
	for (int i = 0; i < 78; i++) {
		PrintAll(head[i]);
	}
}

void Pokecen(User* user) {
	//포켓몬 회복
	POKE* curr = user->poke;
	for (int i = 0; i < user->num_poke; i++) {
		curr->stat.cur_HP = curr->stat.lv_HP;
		curr = curr->link;
	}
	printf("\n+ 포켓몬의 HP가 모두 회복되었습니다! +\n\n");
}

//head에 포켓몬 진화형 저장하기
void fill_head(POKE** head) {
	int dexnum=0, hp=0, att=0, def=0, s_att=0, s_def=0, speed=0;
	char p_name[20] = {0}, type[60] = {0};
	int index = 0;
	FILE* fp = fopen("sogang_poke.txt", "r");
	fscanf(fp, "%d %s %s %d %d %d %d %d %d", &dexnum, p_name, type, &hp, &att, &def, &s_att, &s_def, &speed);
	while (!feof(fp)) {
		//printf("%d %s %s %d %d %d %d %d %d\n", dexnum, p_name, type, hp, att, def, s_att, s_def, speed);
		//fscanf(fp, "%d %s %s %d %d %d %d %d %d", &dexnum, p_name, type, &hp, &att, &def, &s_att, &s_def, &speed);
		
		//변수가 너무 많으니까 newnode 구조체에 담아서 함수의 parameter로 보내기
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

		//head[index] 리스트에서 마지막 노드 구해서 node에 저장
		POKE* node = (POKE*)malloc(sizeof(POKE));
		node = head[index];
		while (1) {
			if (node->link == NULL) break;
			node = node->link;
		}
		
		//도감번호에 따라서 node와 newnode 연결하기
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
				//마지막 진화형 다음에는 head[index]의 index값이 1증가=>다음 포켓몬
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