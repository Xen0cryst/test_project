use chrono::prelude::*;
use sha2::{Digest, Sha256};

#[derive(Debug, Clone)]
struct Block {
    index: u64,
    timestamp: DateTime<Utc>,
    data: String,
    previous_hash: String,
    hash: String,
}

impl Block {
    fn new(index: u64, data: String, previous_hash: String) -> Block {
        let timestamp = Utc::now();
        let hash = Block::calculate_hash(index, &timestamp, &data, &previous_hash);
        Block {
            index,
            timestamp,
            data,
            previous_hash,
            hash,
        }
    }

    fn calculate_hash(index: u64, timestamp: &DateTime<Utc>, data: &str, previous_hash: &str) -> String {
        let input = format!("{}{}{}{}", index, timestamp, data, previous_hash);
        let mut hasher = Sha256::new();
        hasher.update(input);
        format!("{:x}", hasher.finalize())
    }
}

struct Blockchain {
    chain: Vec<Block>,
}

impl Blockchain {
    fn new() -> Blockchain {
        let genesis_block = Block::new(0, String::from("Genesis Block"), String::from("0"));
        Blockchain { chain: vec![genesis_block] }
    }

    fn add_block(&mut self, data: String) {
        let previous_block = self.chain.last().unwrap();
        let new_block = Block::new(previous_block.index + 1, data, previous_block.hash.clone());
        self.chain.push(new_block);
    }
}

fn main() {
    // Create a new blockchain
    let mut blockchain = Blockchain::new();

    // Add blocks to the blockchain
    blockchain.add_block(String::from("Block 1 Data"));
    blockchain.add_block(String::from("Block 2 Data"));
    blockchain.add_block(String::from("Block 3 Data"));

    // Print the blockchain
    for block in &blockchain.chain {
        println!("{:?}", block);
    }
}
