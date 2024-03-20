#include <iostream>
#include <vector>
#include <map>

struct AuctionItem {
    std::string description;
    double reservePrice;
    int numBids;
    double highestBid;
    bool sold;
};

std::map<int, AuctionItem> items;

void setupAuction() {
    std::cout << "Auction Setup\n";
    int itemCount;
    std::cout << "Enter number of items (at least 10): ";
    std::cin >> itemCount;
    if(itemCount < 10) itemCount = 10; // Ensure there are at least 10 items

    for (int i = 0; i < itemCount; ++i) {
        int itemNumber;
        AuctionItem item;
        std::cout << "Enter item number: ";
        std::cin >> itemNumber;
        std::cin.ignore(); // Clear input buffer
        std::cout << "Enter description: ";
        getline(std::cin, item.description);
        std::cout << "Enter reserve price: ";
        std::cin >> item.reservePrice;
        item.numBids = 0;
        item.highestBid = 0.0;
        item.sold = false;
        items[itemNumber] = item;
    }
}
void placeBid() {
    std::cout << "Place a Bid\n";
    int itemNumber, buyerNumber;
    double bid;
    std::cout << "Enter your buyer number: ";
    std::cin >> buyerNumber;
    std::cout << "Enter item number: ";
    std::cin >> itemNumber;

    if (items.find(itemNumber) == items.end()) {
        std::cout << "Item not found.\n";
        return;
    }

    std::cout << "Item description: " << items[itemNumber].description << "\n";
    std::cout << "Current highest bid: " << items[itemNumber].highestBid << "\n";
    std::cout << "Enter your bid: ";
    std::cin >> bid;

    if (bid <= items[itemNumber].highestBid) {
        std::cout << "Your bid must be higher than the current highest bid.\n";
    } else {
        items[itemNumber].highestBid = bid;
        items[itemNumber].numBids++;
        std::cout << "Bid placed successfully.\n";
    }
}
void endAuction() {
    double totalFee = 0.0;
    int itemsSold = 0, belowReserve = 0, noBids = 0;

    for (auto& item : items) {
        if (item.second.numBids > 0 && item.second.highestBid >= item.second.reservePrice) {
            item.second.sold = true;
            totalFee += item.second.highestBid * 0.10;
            itemsSold++;
        } else if (item.second.numBids == 0) {
            noBids++;
        } else {
            belowReserve++;
            std::cout << "Item " << item.first << " did not meet reserve price, final bid: " << item.second.highestBid << "\n";
        }
    }

    std::cout << "Total auction company fee: " << totalFee << "\n";
    std::cout << "Number of items sold: " << itemsSold << "\n";
    std::cout << "Number of items below reserve price: " << belowReserve << "\n";
    std::cout << "Number of items with no bids: " << noBids << "\n";
}

int main() {
    setupAuction();
    char continueBidding = 'y';
    while (continueBidding == 'y' || continueBidding == 'Y') {
        placeBid();
        std::cout << "Continue bidding? (y/n): ";
        std::cin >> continueBidding;
    }
    endAuction();
    return 0;
}
