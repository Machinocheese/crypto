#include <iostream>
#include <vector>
#include <algorithm>

#define u8 uint8_t
using namespace std;

vector<vector<u8> > create_state_array(u8 message[16]){
	vector<vector<u8> > input_array;
	for(int i = 0; i < 4; i++){
		vector<u8> temp;
		for(int j = 0; j < 4; j++){
			temp.push_back(message[j*4+i]);
		}
		input_array.push_back(temp);
	}
	return input_array;
}

u8 sub_bytes(u8 value){
	u8 s_box[16][16] = {{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}, {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};
	int row =  value >> 4;
	int column = value & 15;
	
	return s_box[row][column];
}

u8 inv_sub_bytes(u8 value){
	u8 s_box[16][16] = {{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb}, {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb}, {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e}, {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25}, {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92}, {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84}, {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06}, {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b}, {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73}, {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e}, {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b}, {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4}, {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f}, {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef}, {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61}, {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};	
	int row =  value >> 4;
	int column = value & 15;
	
	return s_box[row][column];
}

vector<vector<u8> > shift_rows(vector<vector<u8> > state_array){
	vector<vector<u8> > copy(state_array);
	for(int i = 0; i < copy.size(); i++){
		rotate(copy[i].begin(), copy[i].begin()+i, copy[i].end());
	}
	return copy;
}

vector<vector<u8> > inv_shift_rows(vector<vector<u8> > state_array){
	vector<vector<u8> > copy(state_array);
	for(int i = 0; i < copy.size(); i++){
		rotate(copy[i].rbegin(), copy[i].rbegin()+i, copy[i].rend());
	}
	return copy;
}

u8 gmul_two(u8 value){
	int result = (value << 1);
	if(result >> 8 == 1){
		result = result ^ 0x1b;
	}
	return result;
}

vector<vector<u8> > mix_columns(vector<vector<u8> > state_array){
	vector<vector<u8> > copy(state_array);
	u8 s0, s1, s2, s3;
	for(int i = 0; i < 4; i++){
		s0 = state_array[0][i];
		s1 = state_array[1][i];
		s2 = state_array[2][i];
		s3 = state_array[3][i];
		
		copy[0][i] = gmul_two(s0) ^ (gmul_two(s1) ^ s1) ^ s2 ^ s3;
		copy[1][i] = s0 ^ gmul_two(s1) ^ (gmul_two(s2) ^ s2) ^ s3;
		copy[2][i] = s0 ^ s1 ^ gmul_two(s2) ^ (gmul_two(s3) ^ s3);
		copy[3][i] = (gmul_two(s0) ^ s0) ^ s1 ^ s2 ^ gmul_two(s3);
	}
	return copy;
}

#define gmul_9(x) gmul_two(gmul_two(gmul_two(x))) ^ x
#define gmul_b(x) gmul_two(gmul_two(gmul_two(x)) ^ x) ^ x
#define gmul_d(x) gmul_two(gmul_two(gmul_two(x) ^ x)) ^ x
#define gmul_e(x) gmul_two(gmul_two(gmul_two(x) ^ x) ^ x)
vector<vector<u8> > inv_mix_columns(vector<vector<u8> > state_array){
	vector<vector<u8> > copy(state_array);
	u8 s0, s1, s2, s3;
	for(int i = 0; i < 4; i++){
		s0 = state_array[0][i];
		s1 = state_array[1][i];
		s2 = state_array[2][i];
		s3 = state_array[3][i];
		
		copy[0][i] = gmul_e(s0) ^ gmul_b(s1) ^ gmul_d(s2) ^ gmul_9(s3);
		copy[1][i] = gmul_9(s0) ^ gmul_e(s1) ^ gmul_b(s2) ^ gmul_d(s3);
		copy[2][i] = gmul_d(s0) ^ gmul_9(s1) ^ gmul_e(s2) ^ gmul_b(s3);
		copy[3][i] = gmul_b(s0) ^ gmul_d(s1) ^ gmul_9(s2) ^ gmul_e(s3);
	}
	return copy;
}

vector<vector<u8> > add_round_key(vector<vector<u8> > state_array, vector<vector<u8> > key){
	vector<vector<u8> > copy(state_array);
	for(int i = 0; i < state_array.size(); i++){
		for(int j = 0; j < state_array[i].size(); j++){
			copy[i][j] = state_array[i][j] ^ key[i][j];
		}
	}
	return copy;
}

vector<vector<vector<u8> > > generate_keys(vector<vector<u8> > state_array){
	vector<vector<vector<u8> > > key_set;
	vector<vector<u8> > copy(state_array);
	vector<u8> selected;
	u8 rcon[10] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

	for(int k = 0; k < 10; k++){ //num-rounds. modify for higher-bits.
		//i think 4 can be used for 128, 196, 256-bit keys.
		for(int i = 0; i < 4; i++){
			selected.push_back(copy[i][copy.size() - 1]);
			selected[i] = sub_bytes(selected[i]);
		}
		rotate(selected.begin(), selected.begin()+1, selected.end());
		for(int i = 0; i < 4; i++){	
		}
		selected[0] = selected[0] ^ rcon[k];
		for(int i = 0; i < 4; i++){ //edit i based on key size
			for(int j = 0; j < 4; j++){
				copy[j][i] = copy[j][i] ^ selected[j];
			}
			selected.clear();
			for(int j = 0; j < 4; j++){
				selected.push_back(copy[j][i]);
			}
		}
		key_set.push_back(copy);
		selected.clear();
	}
	return key_set;
}

void print_state(vector<vector<u8> > test){
	for(int i = 0; i < test.size(); i++){
		for(int j = 0; j < test[i].size(); j++){
			printf("%x ", test[i][j]);
		}	
		cout << endl;
	}
	cout << endl << endl;
}

vector<u8> decrypt(u8 message[16], u8 key[16]){
	vector<vector<u8> > state_array = create_state_array(message);	
	vector<vector<u8> > key_state = create_state_array(key);
	
	vector<vector<vector<u8> > > key_set = generate_keys(key_state);

	state_array = add_round_key(state_array, key_set[key_set.size() - 1]);
	for(int round = 8; round >= 0; round--){
		//shift_rows
		state_array = inv_shift_rows(state_array);
		
		//sub_bytes step
		for(int i = 0; i < state_array.size(); i++){
			for(int j = 0; j < state_array[i].size(); j++){
				state_array[i][j] = inv_sub_bytes(state_array[i][j]);
			}
		}

		//add_round_key
		state_array = add_round_key(state_array, key_set[round]);
		
		//mix_columns <- fucked up
		state_array = inv_mix_columns(state_array);
	}

	for(int i = 0; i < state_array.size(); i++){
		for(int j = 0; j < state_array[i].size(); j++){
			state_array[i][j] = inv_sub_bytes(state_array[i][j]);
		}
	}
	state_array = inv_shift_rows(state_array);
	state_array = add_round_key(state_array, key_state);

	vector<u8> decrypted;
	for(int i = 0; i < state_array.size(); i++){
		for(int j = 0; j < state_array[i].size(); j++){
			decrypted.push_back(state_array[j][i]);
		}
	}
	return decrypted;
}

vector<u8> encrypt(u8 cipher[16], u8 key[16]){
	vector<vector<u8> > state_array = create_state_array(cipher);	
	vector<vector<u8> > key_state = create_state_array(key);
	
	vector<vector<vector<u8> > > key_set = generate_keys(key_state);

	state_array = add_round_key(state_array, key_state);
	for(int round = 0; round < 9; round++){
		//sub_bytes step
		for(int i = 0; i < state_array.size(); i++){
			for(int j = 0; j < state_array[i].size(); j++){
				state_array[i][j] = sub_bytes(state_array[i][j]);
			}
		}

		//shift_rows
		state_array = shift_rows(state_array);

		//mix_columns
		state_array = mix_columns(state_array);

		//add_round_key
		state_array = add_round_key(state_array, key_set[round]);
	}

	for(int i = 0; i < state_array.size(); i++){
		for(int j = 0; j < state_array[i].size(); j++){
			state_array[i][j] = sub_bytes(state_array[i][j]);
		}
	}
	state_array = shift_rows(state_array);
	state_array = add_round_key(state_array, key_set[key_set.size() - 1]);

	vector<u8> encrypted;
	for(int i = 0; i < state_array.size(); i++){
		for(int j = 0; j < state_array[i].size(); j++){
			encrypted.push_back(state_array[j][i]);
		}
	}
	return encrypted;
}

//i'm just going to ignore the fact that i can go over 128 bit keys

int main(int argc, char** argv){
	//16 byte (ASCII characters) - convert to 128 bit array
	u8 message[16] = {0x0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	//u8 message[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x7, 0x34};
	//u8 key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	u8 key[16] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
	u8 cipher[16] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x4, 0x30, 0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};

	cout << "Original message (hex bytes): ";
	for(int i = 0; i < 16; i++){
		printf("%x ", message[i]);
	}
	cout << endl;
	vector<u8> result = encrypt(message, key);
	printf("Encrypted message           : ");
	for(int i = 0; i < result.size(); i++){
		printf("%x ", result[i]);
	}
	cout << endl << "Decrypted message           : ";
	result = decrypt(cipher, key);
	for(int i = 0; i < result.size(); i++){
		printf("%x ", result[i]);
	}
	cout << endl;

}
