Classes:

Top Class
  BOOKS--- contains n Accounts
    - set of n accounts
    - total balances for each type of account
    --funtionality:
      - categorize all spending (in %)
      -
  ACCOUNT--- storage for each account
    - data:
      - account type (savings, checking, brokerage, credit)
      - Name
      - account ID
      - balance
      - if credit, limit on account
    - n transactions
      - unique ID
      - date
      - description
      - type
          - checking - debit, eft, ATM, deposit, check, withdraw
          - savings - check, deposit, eft
          - credit - charge, payment
          - brokerage - deposit, withdraw
      - Major Category
          - Bills, Grocery, Dining, Entertainment, Travel, FEE, ADJUSTMENT, Interest, Saving
      - Minor Category
          - Usually for bills: CC, Student Loans, Rent, Utility, Cable, Phone, Insurance

   - functionality:
      - add transaction
      - remove transaction
      - return summary between dates t1 and t2
          - [category, total amount]
      - return balance
      - return last N transactions
      - return transactions between t1 and t2
      - search for transaction based on:
          - date
          - unique ID
          - type
          - amount
          - category (major, minor)

  Second functionality:
    - Alarm / Recurring payment system.


Essentially:
Base: transaction; defines common functions
CreditTransaction extends transaction
SavingsTransaction extends transaction
CheckingTransaction extends transaction
BrokerageTransaction extends transaction
--Each defines its own categories and types

Base: account; defines commmon functions
CheckingAccount extends account
BrokerageAccount extends account
SavingsAccount extends account
CreditAccount extends account
an account contains a vector of transactions
--each define its own data

Class books:
a book contains a vector/hash of accounts
