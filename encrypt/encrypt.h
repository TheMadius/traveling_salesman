#pragma once
#include "b64.h"
#include "vigenere.h"

std::string _encrypt(const std::string& msg, const std::string& key) {
    return encrypt_vigenere(msg, key);
}


std::string _decrypt(const std::string& encrypted_msg, const std::string& key) {
	std::string newKey = extend_key(encrypted_msg, key);
	return decrypt_vigenere(encrypted_msg, newKey);
}