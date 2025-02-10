# CLI Banking System in C

## Project Overview
A command-line banking management system implemented in C, designed to simulate basic banking operations for a small financial institution.

## Features
- Client Management
  - Insert, list, show, delete, and search clients
  - Maximum of 20 clients per bank
  - Each client can have up to 3 bank accounts

- Account Management
  - Create and close bank accounts
  - List client accounts
  - View account details

- Banking Operations
  - Deposit money
  - Withdraw money
  - Transfer funds between accounts
  - Track banking movements

- Bank Information
  - View total number of clients
  - View total number of accounts
  - Check total bank balance

## Data Model
### Client
- Unique ID
- Name (max 100 characters)
- NIF (9-digit identifier)
- Integrated position (total account balance)

### Bank Account
- Account ID (3 characters)
- Balance
- Banking movements (up to 100 per account)

### Banking Movement
- ID
- Type (Deposit, Withdrawal, Transfer)
- Value

## Project Structure
- `ui.c` and `ui.h`: User Interface (Do not modify)
- `main.c`: Main application logic
- `sgb.c` and `sgb.h`: Banking system management

## Compilation
```bash
make
```

## Testing
```bash
# Run all tests
./test_all.sh

# Test specific functionality
./test_func.sh txx
```

## Development Guidelines
- Follow consistent code formatting
- Add meaningful comments
- Avoid code repetition
- Use constants instead of hardcoded values
- Ensure no compilation warnings

## Evaluation Criteria
- 12/20 points: Automated tests
- 8/20 points: Code quality
  - Abstraction
  - Comments
  - Code organization
  - Compilation errors/warnings
  - Memory management

## Notes
- Only transfers between accounts in the same bank are allowed
- Negative account balances are not permitted
