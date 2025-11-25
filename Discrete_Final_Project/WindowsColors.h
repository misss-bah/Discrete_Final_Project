#ifndef WINDOWSCOLORS_H
#define WINDOWSCOLORS_H

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

// Declare but don't define hConsole here to avoid multiple definition
extern HANDLE g_hConsole;

class WindowsColors {
public:
    // Color enumerations
    enum Color {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        BRIGHT_BLUE = 9,
        BRIGHT_GREEN = 10,
        BRIGHT_CYAN = 11,
        BRIGHT_RED = 12,
        BRIGHT_MAGENTA = 13,
        BRIGHT_YELLOW = 14,
        WHITE = 15
    };

    // Initialize console
    static void initConsole() {
        g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(g_hConsole, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(g_hConsole, dwMode);
    }

    // Set text color
    static void setColor(Color foreground, Color background = BLACK) {
        SetConsoleTextAttribute(g_hConsole, (background << 4) | foreground);
    }

    // Reset to default colors
    static void resetColor() {
        SetConsoleTextAttribute(g_hConsole, LIGHT_GRAY);
    }

    // Print colored text
    static void printColored(Color foreground, Color background, const string& text) {
        setColor(foreground, background);
        cout << text;
        resetColor();
    }

    // Print header with cyan background
    static void printHeader(const string& title) {
        setColor(BRIGHT_CYAN, BLACK);
        cout << "\n" << string(70, '=') << endl;
        cout << "  " << title << endl;
        cout << string(70, '=') << endl;
        resetColor();
    }

    // Print sub-header with yellow
    static void printSubHeader(const string& title) {
        setColor(BRIGHT_YELLOW, BLACK);
        cout << "\n>>> " << title << " <<<\n" << endl;
        resetColor();
    }

    // Print success message (green)
    static void printSuccess(const string& msg) {
        setColor(BRIGHT_GREEN, BLACK);
        cout << "  [?] " << msg << endl;
        resetColor();
    }

    // Print error message (red)
    static void printError(const string& msg) {
        setColor(BRIGHT_RED, BLACK);
        cout << "  [?] " << msg << endl;
        resetColor();
    }

    // Print warning message (yellow)
    static void printWarning(const string& msg) {
        setColor(BRIGHT_YELLOW, BLACK);
        cout << "  [?] " << msg << endl;
        resetColor();
    }

    // Print info message (blue)
    static void printInfo(const string& msg) {
        setColor(BRIGHT_BLUE, BLACK);
        cout << "  [?] " << msg << endl;
        resetColor();
    }

    // Print benchmark result box
    static void printBenchmarkResult(const string& module, long long time) {
        setColor(BRIGHT_CYAN, BLACK);
        cout << "  ???????????????????????????????????????" << endl;
        cout << "  ? Module: " << leftAlign(module, 26) << "?" << endl;
        cout << "  ? Time: " << leftAlign(to_string(time) + " µs", 28) << "?" << endl;
        cout << "  ???????????????????????????????????????" << endl;
        resetColor();
    }

    // Print menu option
    static void printMenuOption(int number, const string& option) {
        setColor(BRIGHT_YELLOW, BLACK);
        cout << "  " << number << ". ";
        resetColor();
        cout << option << endl;
    }

    // Print menu separator
    static void printMenuSeparator() {
        setColor(DARK_CYAN, BLACK);
        cout << string(70, '-') << endl;
        resetColor();
    }

    // Print choice prompt
    static void printChoicePrompt() {
        setColor(BRIGHT_MAGENTA, BLACK);
        cout << "\n  Enter your choice: ";
        resetColor();
    }

    // Print section header
    static void printSection(const string& title) {
        setColor(BRIGHT_MAGENTA, BLACK);
        cout << "\n" << string(70, '-') << endl;
        cout << "  " << title << endl;
        cout << string(70, '-') << endl;
        resetColor();
    }

    // Print progress bar
    static void printProgressBar(int current, int total, const string& label = "") {
        setColor(BRIGHT_GREEN, BLACK);
        int barWidth = 50;
        int filled = (current * barWidth) / total;

        cout << "  " << label << " [";
        for (int i = 0; i < barWidth; ++i) {
            if (i < filled) cout << "?";
            else cout << "?";
        }
        cout << "] " << current << "/" << total << endl;
        resetColor();
    }

    // Print stats box
    static void printStatsBox(const string& label, const string& value) {
        setColor(BRIGHT_CYAN, BLACK);
        cout << "  ???????????????????????????????????????" << endl;
        cout << "  ? " << leftAlign(label + ":", 35) << " ?" << endl;
        cout << "  ? " << leftAlign(value, 35) << " ?" << endl;
        cout << "  ???????????????????????????????????????" << endl;
        resetColor();
    }

    // Print list item
    static void printListItem(int index, const string& item) {
        setColor(BRIGHT_YELLOW, BLACK);
        cout << "  [" << index << "] ";
        resetColor();
        cout << item << endl;
    }

    // Clear screen
    static void clearScreen() {
        system("cls");
    }

    // Pause for user input
    static void pause() {
        setColor(BRIGHT_MAGENTA, BLACK);
        cout << "\n  Press Enter to continue...";
        resetColor();
        cin.ignore();
        cin.get();
    }

    // Print table header
    static void printTableHeader(const string& col1, const string& col2, const string& col3) {
        setColor(BRIGHT_CYAN, BLACK);
        cout << "  ??????????????????????????????????????????????" << endl;
        cout << "  ? " << centerInBox(col1, 12) << " ? "
            << centerInBox(col2, 12) << " ? "
            << centerInBox(col3, 12) << " ?" << endl;
        cout << "  ??????????????????????????????????????????????" << endl;
        resetColor();
    }

    // Print table row
    static void printTableRow(const string& col1, const string& col2, const string& col3) {
        cout << "  ? " << centerInBox(col1, 12) << " ? "
            << centerInBox(col2, 12) << " ? "
            << centerInBox(col3, 12) << " ?" << endl;
    }

    // Print table footer
    static void printTableFooter() {
        setColor(BRIGHT_CYAN, BLACK);
        cout << "  ============================================" << endl;
        resetColor();
    }

    // Print dual stats box
    static void printDualStatsBox(const string& label1, const string& value1,
        const string& label2, const string& value2) {
        setColor(BRIGHT_CYAN, BLACK);
        cout << "  ============================================" << endl;
        cout << "  = " << leftAlign(label1 + ":", 18) << " = " << leftAlign(label2 + ":", 18) << " ?" << endl;
        cout << "  = " << leftAlign(value1, 18) << "  " << leftAlign(value2, 18) << " ?" << endl;
        cout << " =============================================" << endl;
        resetColor();
    }

private:
    // Helper: left align text
    static string leftAlign(const string& text, int width) {
        if ((int)text.length() >= width) return text.substr(0, width);
        return text + string(width - text.length(), ' ');
    }

    // Helper: center in box
    static string centerInBox(const string& text, int width) {
        if ((int)text.length() >= width) return text.substr(0, width);
        int spaces = (width - (int)text.length()) / 2;
        int totalSpaces = width - (int)text.length();
        return string(spaces, ' ') + text + string(totalSpaces - spaces, ' ');
    }
};

#endif
