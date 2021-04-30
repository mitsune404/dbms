#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct student_record {

	  int std_id;
	     name[256];
	       float gpa;

}student, scan;


int int_input_validity_and_assign(int *number) {

	  char string[256];
	    char *ptr;
	      int num;

	        fgets(string, sizeof(string), stdin);

		  /* strtol function returns integers from character arrays and assigns the first non integer character to the pointer character passed to it as the second input
		   *   
		   *       there is also strtod which is the same but for float values */

		  num = strtol(string, &ptr, 10);

		    if (string[0] == '\n') {
			        *ptr = '\0';
				  }

		      /* if the string doesnt contain any non number characters *ptr will be empty, so */
		      if (*ptr == '\n' ) {
			          *number = num;
				      return 1;
				        }
		        else {
				    printf("Invalid input... Enter value again : ");
				        return 0;
					  }
} 


int float_input_validity_and_assign(float *number) {
	  char string[256];
	    char *ptr;
	      float num;

	        fgets(string, sizeof(string), stdin);

		  num = strtod(string, &ptr);

		    /* exceptional case */
		    if (string[0] == '\n') {
			        *ptr = '\0';
				  }

		      if (*ptr == '\n' ) {
			          *number = num;
				      return 1;
				        }
		        else {
				    printf("Invalid input... Enter value again : ");
				        return 0;
					  }
}

int action_1() {
	  FILE *record = fopen("record.dat", "ab+");
	    int loop = 0, i = 0, validity = 0, file_size = 0;

	      if (record != NULL) {

		          do {
				        
				        i++;

					      fseek(record, 0, SEEK_END);
					            file_size = ftell(record);
						          rewind(record);

							        printf("\n****************************************\n");

								      printf("> School ID of student %d : ", i);
								            do {
										            validity = int_input_validity_and_assign(&student.std_id);

											            do {
													              fread(&scan, sizeof(record), 1, record);
														              } while (scan.std_id != student.std_id && ftell(record) != file_size);

												            if (scan.std_id == student.std_id) {
														              printf("Student ID already exists, please enter a different value : ");
															                validity = 0;
																	        }

												          } while (validity != 1);


									          printf("\n> Full name of student %d : ", i);
									          do {
											          fgets(student.name, sizeof(student.name), stdin);
												          fseek(record, 0, SEEK_SET);
													          
													          if ( student.name[0] == '\n' || student.name[0] == ' ') {
															            printf("Invalid input... Enter value again : ");
																            }

														        } while (student.name[0] == '\n' || student.name[0] == ' ');

										        printf("\n> Enter GPA of student %d : ", i);
										        do {
												        validity = float_input_validity_and_assign(&student.gpa);

													        if (student.gpa > 5 && validity==1) {
															          validity = 0;
																            printf("> GPA cannot be greater than 5.0. Enter value again : ");
																	            }
														      } while (validity != 1);

											      printf("\n****************************************\n");

											      fwrite(&student, sizeof(student), 1, record);


											            printf("Press 1 to enter another record, 2 to go back to main menu and 3 to quit : ");
												          do {
														          validity = int_input_validity_and_assign(&loop);

															          if (loop != 1 && loop != 2 && loop != 3 && validity == 1) {
																	            validity = 0;
																		              printf("Invalid input... Enter value again : ");
																			              }
																        } while (validity != 1);

													      } while (loop == 1);

			      fclose(record);
			    }
	        else {
			    printf("Fatal error. Couldn't open record file.");
			        return 0;
				  }

		  return loop;
}

/*action 2 supplement function */
int search_algo(char name1[256], char name2[256]) {
	  int i = 0, j = 0, size = 0, check = 0;

	    while (name1[size] != '\n') {
		        size++;
			  }
	        
	      while ( name1[i] != '\n' && name2[j] != '\n') {
		          
		          if ( toupper(name1[i]) == toupper(name2[j]) ) {
				        i++;
					      j++;
					            check++;
						        }
			      else {
				            i = 0;
					          j++;
						        check = 0;
							    }

			        }

	        if (check == size) {
			    return 1;
			      }
		  else {
			      return 0;
			        }
}

/* looking up an entry */
int action_2() {

	  FILE *record = fopen("record.dat", "ab+");
	    int loop = 1, search_type = 0, validity = 0, std_id = 0, file_size = 0;
	      char name[255];

	        if (record != NULL) {
			    fseek(record, 0, SEEK_END);
			        file_size = ftell(record);

				    do {
					          printf("\nPress 1 to look up an entry using student ID and 2 to look up using a name : ");
						        do {
								        validity = int_input_validity_and_assign(&search_type);

									        if (search_type != 1 && search_type != 2 && validity == 1) {
											            validity = 0;
												                printf("Invalid input... Enter value again : ");
														        }
										      } while (validity != 1);
							    
							      if (search_type == 1) {
								              printf("Enter ID of the student : ");
									              do {
											              validity = int_input_validity_and_assign(&std_id);
												              } while (validity != 1);

										              fseek(record, 0, SEEK_SET);

										              do {
												                fread(&scan, sizeof(scan), 1, record);
														        } while (scan.std_id != std_id && ftell(record) != file_size);

											              if (scan.std_id == std_id) {
													              
													                printf("\n****************************************\n");
															          printf("Roll Number : %d", scan.std_id);
																            printf("\nName : %s", scan.name);
																	              printf("GPA : %f", scan.gpa);
																		                printf("\n****************************************\n");

																				        }
											              else {
													                printf("No entry with matching student ID found");
															        }

											            }

							      else if (search_type == 2) {
								              printf("Enter name of the student : ");
									              do {
											                fgets(name, sizeof(name), stdin);
													          if ( name[0] == '\n' || name[0] == ' ') {
															            printf("Invalid input... Enter value again : ");
																              } 
														          }while (name[0] == '\n' || name[0] == ' ');

										              rewind(record);

										              do {
												                fread(&scan, sizeof(scan), 1, record);

														          if (search_algo(name, scan.name) == 1) {
																          
																              printf("\n****************************************\n");
																	                  printf("Roll Number : %d", scan.std_id);
																			              printf("\nName : %s", scan.name);
																				                  printf("GPA : %f", scan.gpa);
																						              printf("\n****************************************\n");

																							                }
															          } while ( ftell(record) != file_size);

											            }


							      printf("\nPress 1 to look for another record, 2 to go back to main menu and 3 to quit : ");
							            do {
									            validity = int_input_validity_and_assign(&loop);

										            if (loop != 1 && loop != 2 && loop != 3 && validity == 1) {
												              validity = 0;
													                printf("Invalid input... Enter value again : ");
															        }
											          } while (validity != 1);

								        } while (loop == 1);

				        fclose(record);
				        }
		  else {
			      printf("Fatal error. Couldn't open record file.");
			          return 0;
				    }
		    return loop;
}

int action_3() {
	  int validity = 0, loop = 0, file_size = 0;

	    FILE *record = fopen("record.dat", "r");

	      if (record != NULL) {

		          fseek(record, 0, SEEK_END);
			      file_size = ftell(record);
			          rewind(record);

				      while ( file_size != ftell(record)) {

					            fread(&scan, sizeof(scan), 1, record);

						          printf("\n****************************************\n");
							        printf("Roll Number : %d", scan.std_id);
								      printf("\nName : %s", scan.name);
								            printf("GPA : %f", scan.gpa);
									          printf("\n****************************************\n");

										      }
				        
				        }
	        else {
			    printf("Fatal error. Couldn't open record file.");
			        return 0;
				  }

		  fclose(record);

		    printf("\nPress 1 to go back to main menu and 2 to quit : ");
		          do {
				          validity = int_input_validity_and_assign(&loop);

					          if (loop != 1 && loop != 2 && validity == 1) {
							            validity = 0;
								              printf("Invalid input... Enter value again : ");
									              }
						        } while (validity != 1);

			    loop++;

			    return loop;
}

int action_4() {

	  FILE *record = fopen("record.dat", "r+");
	    int loop = 1, validity = 0, std_id = 0, file_size = 0, search = 0;

	      if (record != NULL) {

		          fseek(record, 0, SEEK_END);
			      file_size = ftell(record);


			          do {
					        rewind(record);

						      printf("\nEnter Student ID : ");
						            do {
								            validity = int_input_validity_and_assign(&std_id); 
									          } while (validity != 1);

							          /* edit algo */
							          
							          do {
									          fread(&scan, sizeof(scan), 1, record);

										          if (scan.std_id == std_id) {
												            search = 1;
													              fseek(record, -sizeof(scan), SEEK_CUR);

														                printf("\n****************************************\n");
																          printf("Please enter new detail for Student ID %d ", std_id);

																	            student.std_id = std_id;

																		              printf("\n> Full name of student  : ");
																			                do {
																						            fgets(student.name, sizeof(student.name), stdin);
																							            
																							                if ( student.name[0] == '\n' || student.name[0] == ' ') {
																										            printf("Invalid input... Enter value again : ");
																											                }

																									          } while (student.name[0] == '\n' || student.name[0] == ' ');

																					          printf("\n> Enter GPA of student : ");
																					          do {
																							              validity = float_input_validity_and_assign(&student.gpa);

																								                  if (student.gpa > 5 && validity==1) {
																											                validity = 0;
																													              printf("> GPA cannot be greater than 5.0. Enter value again : ");
																														                  }
																										            } while (validity != 1);

																						            printf("\n****************************************\n");

																						            fwrite(&student, sizeof(student), 1, record);
																							            }
											          
											        } while (scan.std_id != std_id && ftell(record) != file_size);
							          

							          if (search == 0) {
									          printf("No student entry with matching ID found");
										        }


							          printf("\nPress 1 to edit another record, 2 to go back to main menu and 3 to quit : ");
								        do {
										        validity = int_input_validity_and_assign(&loop);

											        if (loop != 1 && loop != 2 && loop != 3 && validity == 1) {
													          validity = 0;
														            printf("Invalid input... Enter value again : ");
															            }
												      } while (validity != 1);

									    } while (loop == 1);

				      fclose(record);

				    }
	        else {
			    printf("Fatal error. Couldn't open record file.");
			        return 0;
				  }
		  return loop;
}

int action_5 () {


	  FILE *record = fopen("record.dat", "r+"), *buffer = fopen("record.dat.buff", "w+");

	    int loop = 1, validity = 0, std_id = 0, file_size = 0, file_size_buffer = 0, search = 0;

	      if (record != NULL && buffer != NULL) {

		          fseek(record, 0, SEEK_END);
			      file_size = ftell(record);

			          do {
					        rewind(record);

						      printf("\nEnter Student ID : ");
						            do {
								            validity = int_input_validity_and_assign(&std_id); 
									          } while (validity != 1);


							          /* edited recreation */

							          do {
									          fread(&scan, sizeof(scan), 1, record);

										          if (scan.std_id != std_id) {
												            fwrite(&scan, sizeof(scan), 1, buffer);
													            }
											          else if (scan.std_id == std_id) {
													            fseek(record, 1, SEEK_CUR);
														              search = 1;
															              }
												          
												        } while (ftell(record) != file_size);

							          rewind(record);
							          

							          fseek(buffer, 0, SEEK_END);
								        file_size_buffer = ftell(buffer);
									      rewind(buffer);


									            if (search == 1) {
											            do {
													              fread(&scan, sizeof(scan), 1, buffer);

														                fwrite(&scan, sizeof(scan), 1, record);
																        
																        } while (ftell(buffer) != file_size_buffer);

												          }
										          else if (search == 0) {
												          printf("No student entry with matching ID found");
													        }

											        printf("\nPress 1 to delete another record, 2 to go back to main menu and 3 to quit : ");
												      do {
													              validity = int_input_validity_and_assign(&loop);
														       
														              if (loop != 1 && loop != 2 && loop != 3 && validity == 1) {
																                validity = 0;
																		          printf("Invalid input... Enter value again : ");
																			          }
															            } while (validity != 1);

												          } while (loop == 1);

				      fclose(record);
				      fclose(buffer);

				        }
	        else {
			    printf("Fatal error. Couldn't open record file.");
			        return 0;
				  }
		  return loop;

}

int main_menu() {
	  int input_validity = 0;
	    int action = 0;
	      int status = 0;
	        

	        printf("\n\n++:::STUDENT DATABSE MANAGEMENT SYSTEM:::++\n\nActions :\n\n1. New student entry\n2. Look up an entry\n3. Show all entries\n4. Modify existing record \n5. Delete an entry \n6. Quit the application \n\nEnter action serial number to continue : ");

		  do {
			      input_validity = int_input_validity_and_assign(&action);
			          
			          if (action > 6 && action < 0 && input_validity == 1) {
					        input_validity = 0;
						      printf("Invalid input... Enter value again : ");
						          }
				    } while (input_validity != 1);

		    if (action == 1) {
			        status = action_1();
				  }
		    else if (action == 2) {
			        status = action_2();
				  }
		    else if (action == 3) {
			        status = action_3();
				  }
		    else if (action == 4) {
			        status = action_4();
				  }
		    else if (action == 5) {
			        status = action_5();
				  }
		    else if (action == 6) {

			        return 0;
				    
				  }


		    if (status == 2) {
			       return 1;
			         }
		      else if (status == 3) {
			         return 0;
				   }
		        else {
				   return -1; /*unexpected error*/
				     }
}

int main() {
	  int running = 0;

	    do {
		        running = main_menu();
			  } while(running == 1);
	      
}
