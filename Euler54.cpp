// Copyright 2020 Ahmed Alseba

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Checks if suites of hand dealt are the same
bool isSameSuite(char* suites) {
    bool result = (suites[0] == suites[1]) && (suites[0] == suites[2]) && 
        (suites[0] == suites[3]) && (suites[0] == suites[4]);
    return result;
}

// Checks if values of a hand are consecutive
bool isConsecutive(int* values) {
    sort(values, values + 5);
    bool result = (values[4] == values[3] + 1) && (values[3] == values[2] + 1)
        && (values[2] == values[1] + 1) && (values[1] == values[0] + 1);
    if (values[0] == 2 && values[1] == 3 && values[2] == 4 && values[3] == 5
        && values[4] == 14) result = true;
    return result;
}

// Bins hand values
void countValues(int* values, int* count) {
    for (int i = 0; i < 5; i++)
        count[values[i]]++;
}

int main()
{
    int t = 0; // Number of tests

    string input;
    cin >> t;
    
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < 10; j++) {
            string temp;
            cin >> temp;
            input.append(temp);
        }
    }

    if (t > 0 && t < 1001) {
        for (int i = 0; i < t; i++) {
            char inp_temp[2]; // Temp variable for parsing input from console


            int p1_input_value[5] = { 0 };
            char p1_input_suite[5] = { 0 };
            int p2_input_value[5] = { 0 };
            char p2_input_suite[5] = { 0 };

            // Read Player 1's hand
            for (int j = 0; j < 5; j++) {
                inp_temp[0] = input.at(20 * i + 2 * j);
                inp_temp[1] = input.at(20 * i + 2 * j + 1);

                p1_input_suite[j] = inp_temp[1];

                // Convert 10, J, Q, K, A into numerical values
                if (inp_temp[0] == 'T')
                    p1_input_value[j] = 10;
                else if (inp_temp[0] == 'J')
                    p1_input_value[j] = 11;
                else if (inp_temp[0] == 'Q')
                    p1_input_value[j] = 12;
                else if (inp_temp[0] == 'K')
                    p1_input_value[j] = 13;
                else if (inp_temp[0] == 'A')
                    p1_input_value[j] = 14;
                else
                    p1_input_value[j] = inp_temp[0] - '0';
            }

            // Read Player 2's hand
            for (int j = 0; j < 5; j++) {
                inp_temp[0] = input.at(20 * i + 2 * j + 10);
                inp_temp[1] = input.at(20 * i + 2 * j + 11);

                p2_input_suite[j] = inp_temp[1];

                // Convert 10, J, Q, K, A into numerical values
                if (inp_temp[0] == 'T')
                    p2_input_value[j] = 10;
                else if (inp_temp[0] == 'J')
                    p2_input_value[j] = 11;
                else if (inp_temp[0] == 'Q')
                    p2_input_value[j] = 12;
                else if (inp_temp[0] == 'K')
                    p2_input_value[j] = 13;
                else if (inp_temp[0] == 'A')
                    p2_input_value[j] = 14;
                else
                    p2_input_value[j] = inp_temp[0] - '0';
            }

            // Rank 1 = Royal Flush, Rank 10 = Highest card
            int p1_rank = 0;
            int p2_rank = 0;

            // Check Player 1's rank
            int* p1_count = new int[15];
            for (int i = 0; i < 15; i++)
                p1_count[i] = 0;
            countValues(p1_input_value, p1_count);

            int* p1_count_end = p1_count + 15;

            // Pointers indicating the values of repeated cards if applicable
            int* p1_found_four = find(p1_count, p1_count + 15, 4);
            int* p1_found_three = find(p1_count, p1_count + 15, 3);
            int* p1_found_two = find(p1_count, p1_count + 15, 2);
            int* p1_found_two_again = find(p1_found_two + 1, p1_count + 15, 2);

            // Indicates smallest non-repeated value on hand
            int* p1_found_one = find(p1_count, p1_count + 15, 1); 
            // Indicates second largest non-repeated value on hand
            int* p1_found_one_again = find(p1_found_one + 1, p1_count + 15, 1);
            // Indicates largest non-repeated value on hand
            int* p1_found_one_again_again = 
                find(p1_found_one_again + 1, p1_count + 15, 1);

            if (isSameSuite(p1_input_suite)) {
                if (isConsecutive(p1_input_value)) {
                    if (p1_input_value[0] == 2 && p1_input_value[4] == 14) {
                        p1_input_value[4] = 1;
                        p1_rank = 2;
                    }
                    else if (p1_input_value[0] == 10)
                        p1_rank = 1;
                    else
                        p1_rank = 2;
                }
                else
                    p1_rank = 5;
            }
            else if (p1_found_four != p1_count_end)
                p1_rank = 3;
            else if (p1_found_three != p1_count_end 
                && p1_found_two != p1_count_end)
                p1_rank = 4;
            else if (p1_found_three != p1_count_end)
                p1_rank = 7;
            else if (p1_found_two_again != p1_count_end)
                p1_rank = 8;
            else if (p1_found_two != p1_count_end)
                p1_rank = 9;
            else if (isConsecutive(p1_input_value)) {
                if (p1_input_value[0] == 2 
                    && p1_input_value[4] == 14) {
                    p1_input_value[4] = 1;
                    p1_rank = 6;
                }
                p1_rank = 6;
            }
            else p1_rank = 10;

            // Check Player 2's rank
            int* p2_count = new int[15];
            for (int i = 0; i < 15; i++)
                p2_count[i] = 0;
            countValues(p2_input_value, p2_count);

            int* p2_count_end = p2_count + 15;

            // Pointers indicating the values of repeated cards if applicable
            int* p2_found_four = find(p2_count, p2_count + 15, 4);
            int* p2_found_three = find(p2_count, p2_count + 15, 3);
            int* p2_found_two = find(p2_count, p2_count + 15, 2);
            int* p2_found_two_again = find(p2_found_two + 1, p2_count + 15, 2);
            int* p2_found_one = find(p2_count, p2_count + 15, 1);
            int* p2_found_one_again = find(p2_found_one + 1, p2_count + 15, 1);
            int* p2_found_one_again_again = 
                find(p2_found_one_again + 1, p2_count + 15, 1);

            if (isSameSuite(p2_input_suite)) {
                if (isConsecutive(p2_input_value)) {
                    if (p2_input_value[0] == 2 && p2_input_value[4] == 14) {
                        p2_input_value[4] = 1;
                        p2_rank = 2;
                    }
                    else if (p2_input_value[0] == 10)
                        p2_rank = 1;
                    else
                        p2_rank = 2;
                }
                else
                    p2_rank = 5;
            }
            else if (p2_found_four != p2_count_end)
                p2_rank = 3;
            else if (p2_found_three != p2_count_end 
                && p2_found_two != p2_count_end)
                p2_rank = 4;
            else if (p2_found_three != p2_count_end)
                p2_rank = 7;
            else if (p2_found_two_again != p2_count_end)
                p2_rank = 8;
            else if (p2_found_two != p2_count_end)
                p2_rank = 9;
            else if (isConsecutive(p2_input_value)) {
                if (p2_input_value[0] == 2
                    && p2_input_value[4] == 14) {
                    p2_input_value[4] = 1;
                    p2_rank = 6;
                }
                p2_rank = 6;
            }
            else p2_rank = 10;

            // This section of the code checks rank and
            // if ranks are equal it attempts to break them
            if (p1_rank < p2_rank)
                cout << "Player 1\n";
            else if (p1_rank > p2_rank)
                cout << "Player 2\n";
            else
            {
                switch (p1_rank) {
                    case 2: // Straight flush
                        if (p1_input_value[4] > p2_input_value[4])
                            cout << "Player 1\n";
                        else if (p1_input_value[4] < p2_input_value[4])
                            cout << "Player 2\n";
                        break;
                    case 3:
                    {
                        if (p1_found_four - p1_count > p2_found_four - p2_count)
                            cout << "Player 1\n";
                        else if (p1_found_four - p1_count 
                            < p2_found_four - p2_count)
                            cout << "Player 2\n";
                        else if (p1_found_one - p1_count 
                            > p2_found_one - p2_count)
                            cout << "Player 1\n";
                        else if (p1_found_one - p1_count 
                            < p2_found_one - p2_count)
                            cout << "Player 2\n";
                        break; 
                    }
                    case 4:
                        if (p1_found_three - p1_count 
                            > p2_found_three - p2_count)
                            cout << "Player 1\n";
                        else if (p1_found_three - p1_count 
                            < p2_found_three - p2_count)
                            cout << "Player 2\n";
                        else if (p1_found_two - p1_count 
                            > p2_found_two - p2_count)
                            cout << "Player 1\n";
                        else if (p1_found_two - p1_count 
                            < p2_found_two - p2_count)
                            cout << "Player 2\n";
                        break;
                    case 5:
                        for (int i = 4; i >= 0; i--) {
                            if (p1_input_value[i] > p2_input_value[i]) {
                                cout << "Player 1\n";
                                break;
                            }
                            else if (p1_input_value[i] < p2_input_value[i]) {
                                cout << "Player 2\n";
                                break;
                            }
                        }
                        break;
                    case 6:
                        if (p1_input_value[4] > p2_input_value[4])
                            cout << "Player 1\n";
                        else if (p1_input_value[4] < p2_input_value[4])
                            cout << "Player 2\n";
                        else
                            cout << "Unknown\n";
                        break;
                    case 7:
                        if (p1_found_three - p1_count 
                        > p2_found_three - p2_count)
                            cout << "Player 1\n";
                        else if (p1_found_three - p1_count 
                            < p2_found_three - p2_count)
                            cout << "Player 2\n";
                        else {
                            for (int i = 0; i < 2; i++)
                            {
                                if (i == 0) {
                                    if (p1_found_one_again - p1_count 
                            > p2_found_one_again - p2_count) {
                                        cout << "Player 1\n";
                                        break;
                                    }
                                    else if (p1_found_one_again - p1_count 
                                        < p2_found_one_again - p2_count) {
                                        cout << "Player 2\n";
                                        break;
                                    }
                                }
                                else if (i == 1) {
                                    if (p1_found_one - p1_count 
                                        > p2_found_one - p2_count) {
                                        cout << "Player 1\n";
                                        break;
                                    }
                                    else if (p1_found_one - p1_count 
                                        < p2_found_one - p2_count) {
                                        cout << "Player 2\n";
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    case 8:
                        for (int i = 0; i < 3; i++)
                        {
                            if (i == 0) {
                                if (p1_found_two_again - p1_count 
                        > p2_found_two_again - p2_count) {
                                    cout << "Player 1\n";
                                    break;
                                }
                                else if (p1_found_two_again - p1_count 
                                    < p2_found_two_again - p2_count) {
                                    cout << "Player 2\n";
                                    break;
                                }
                            }
                            else if (i == 1) {
                                if (p1_found_two - p1_count 
                                    > p2_found_two - p2_count) {
                                    cout << "Player 1\n";
                                    break;
                                }
                                else if (p1_found_two - p1_count 
                                    < p2_found_two - p2_count) {
                                    cout << "Player 2\n";
                                    break;
                                }
                            }
                            else if (i == 2) {
                                if (p1_found_one - p1_count 
                                    > p2_found_one - p2_count) {
                                    cout << "Player 1\n";
                                    break;
                                }
                                else if (p1_found_one - p1_count 
                                    < p2_found_one - p2_count) {
                                    cout << "Player 2\n";
                                    break;
                                }
                            }
                        }
                    break;
                    case 9:
                        if (p1_found_two - p1_count > p2_found_two - p2_count)
                            cout << "Player 1\n";
                        else if (p1_found_two - p1_count 
                            < p2_found_two - p2_count)
                            cout << "Player 2\n";
                        else {
                            for (int i = 0; i < 3; i++)
                            {
                                if (i == 0) {
                                    if (p1_found_one_again_again - p1_count 
                            > p2_found_one_again_again - p2_count) {
                                        cout << "Player 1\n";
                                        break;
                                    }  
                                    else if (p1_found_one_again_again - p1_count 
                                        < p2_found_one_again_again - p2_count) {
                                        cout << "Player 2\n";
                                        break;
                                    }
                                }
                                else if (i == 1) {
                                    if (p1_found_one_again - p1_count 
                                        > p2_found_one_again - p2_count) {
                                        cout << "Player 1\n";
                                        break;
                                    }
                                    else if (p1_found_one_again - p1_count 
                                        < p2_found_one_again - p2_count) {
                                        cout << "Player 2\n";
                                        break;
                                    }
                                }
                                else if (i == 2) {
                                    if (p1_found_one - p1_count 
                                        > p2_found_one - p2_count) {
                                        cout << "Player 1\n";
                                        break;
                                    }
                                    else if (p1_found_one - p1_count 
                                        < p2_found_one - p2_count) {
                                        cout << "Player 2\n";
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        for (int i = 4; i >= 0; i--) {
                            if (p1_input_value[i] > p2_input_value[i]) {
                                cout << "Player 1\n";
                                break;
                            }
                            else if (p1_input_value[i] < p2_input_value[i]) {
                                cout << "Player 2\n";
                                break;
                            }
                        }
                        break;
                        break;
                }
            }
            delete[] p1_count;
            delete[] p2_count;
        }
    }
}
