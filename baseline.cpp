#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
int last = 0;
class NQueens {
private:
    int size;
    // if we have board 2x2
    // and rows are:
        // .*
        // *.
    //where * is queen
    // then board[0] = 1 and board[1] = 0
    // index is col value is row
    // board[col] = row
    std::vector<int> board;
    std::vector<int> bestBoard;
    std::mt19937 rng;
    int n;
public:
    NQueens(int size)
            : n(size), board(size), bestBoard(size),
              rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count()) {};

    void initState(std::vector<int> &state) {
        std::uniform_int_distribution<int> dist(0, n-1);
        for (int col = 0; col < n; col++) {
            state[col] = dist(rng);
        }
    }
    int countConflicts(const std::vector<int>& state) const{
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if(state[i] == state[j]) {
                    count++;
                }
                if (abs(state[i] - state[j]) == abs(i - j)) {
                    count++;
                }
            }
        }
        return count;
    }
    std::vector<int> randomNeighbor(const std::vector<int>& state) {
        std::vector<int> neighbor = state;
        std::uniform_int_distribution<int> colDist(0, n-1);
        std::uniform_int_distribution<int> rowDist(0, n-1);

        int col = colDist(rng);
        int newRow = rowDist(rng);

        while (newRow == neighbor[col]) {
            newRow = rowDist(rng);
        }
        neighbor[col] = newRow;
        return neighbor;
    }

    double random01() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(rng);
    }
    std::vector<int> simulatedAnnealing(double initialTemp = 1000.0,
                                         double coolingRate = 0.9995,
                                         double minTemp = 0.0001,
                                         int maxIterations = 500000) {
        initState(board);
        bestBoard = board;

        int currentConflicts = countConflicts(board);
        int bestCountConflict = currentConflicts;

        double temp = initialTemp;
        int iteration = 0;

        while (temp > minTemp && iteration < maxIterations) {
            if(currentConflicts == 0) {
                break;
            }
            std::vector<int> neighbor = randomNeighbor(board);
            int neighborConflicts = countConflicts(neighbor);
            if (neighborConflicts < currentConflicts) {
                board = neighbor;
                currentConflicts = neighborConflicts;
            } else {
                double delta = neighborConflicts - currentConflicts;
                double probability = exp(-delta / temp);
                if (random01() < probability) {
                    board = neighbor;
                    currentConflicts = neighborConflicts;
                }
            }
            if (currentConflicts < bestCountConflict) {
                bestBoard = board;
                bestCountConflict = currentConflicts;
            }
            temp *= coolingRate;
            iteration++;
        }
        if (last == 1) {
            std::cout << "Iterations: " << iteration << "\n";
            std::cout << "Best conflicts: " << bestCountConflict << "\n";
        }

        return bestBoard;
    }
    void printBoardVector(const std::vector<int>& state) const {
        std::cout << "\n";
        std::cout << "Board representation:\n";
        for (int i = 0; i < n; i++) {
            std::cout << state[i] << " ";
        }
        std::cout << "\n";

    }
    void printChessboard(const std::vector<int>& state) const {
        std::cout << "\n";
        std::cout << "Chessboard:\n";
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (state[col] == row) {
                    std::cout << "Q ";
                }
                else {
                    std::cout << ". ";
                }
            }
            std::cout << "\n";
        }
    }
};

int main() {
    int n = 100;
    int runs = 30;
    int bestOverall = 1e9;

    std::vector<int> bestSolution;
    int solveCount = 0;

    for (int i = 0; i < runs; i++) {
        NQueens solver(n);
        std::vector<int> solution = solver.simulatedAnnealing(
                1000.0,
                0.9995,
                0.0001,
                500000
        );

        int conflicts = solver.countConflicts(solution);

        if (conflicts < bestOverall) {
            bestOverall = conflicts;
            bestSolution = solution;
        }

        if (conflicts == 0) {
            solveCount++;
        }

        std::cout << "Run " << i + 1 << ": " << conflicts << " conflicts\n";
    }

    double successRate = 100.0 * solveCount / runs;

    std::cout << "Success rate in " << runs << " runs is "
              << successRate << "%.\n";
    std::cout << "Best overall conflicts: " << bestOverall << "\n";
    if (!bestSolution.empty()) {
        last = 1;
        NQueens printer(n);
        printer.printBoardVector(bestSolution);
        printer.printChessboard(bestSolution);
    }
    return 0;
}
