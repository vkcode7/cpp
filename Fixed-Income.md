
### What is the SOFR Rate?
The SOFR (Secured Overnight Financing Rate) is a benchmark interest rate for U.S. dollar-denominated loans and derivatives. It reflects the cost of borrowing cash overnight collateralized by U.S. Treasury securities in the repo market.

#### Key Features of SOFR
- Secured: Based on transactions secured by U.S. Treasuries.
- Overnight: Represents the cost of overnight borrowing.
- Transaction-Based: Derived from actual market transactions rather than estimates, making it robust and transparent.
- Risk-Free: Considered nearly risk-free due to the U.S. Treasury collateral.

SOFR was introduced as an alternative to LIBOR, which was phased out due to concerns about its reliability and susceptibility to manipulation.

#### SOFR Rates Published Daily
The following SOFR-related rates are published each business day:

##### Daily SOFR:
- Reflects the weighted average of overnight repo transactions secured by U.S. Treasuries.
- Published at approximately 8:00 a.m. (ET) for the prior business day.

**SOFR Averages:**
- 30-day SOFR Average
- 90-day SOFR Average
- 180-day SOFR Average

These are compounded averages of SOFR over the specified periods.

SOFR Index: A cumulative compounded value based on daily SOFR rates, used to calculate interest accruals over custom periods.

#### Who Publishes SOFR?
The Federal Reserve Bank of New York (NY Fed) is responsible for calculating and publishing SOFR rates. They gather data from the overnight repo market, ensuring transparency and accuracy.

#### Challenges in Adopting SOFR
- No Term Structure:
SOFR is an overnight rate, while LIBOR provided term rates (e.g., 3-month LIBOR).
Term SOFR rates are being developed but adoption is ongoing.
- Operational Changes:
Financial institutions had to update systems to handle daily compounding calculations.
- Credit Risk Premium:
SOFR lacks LIBOR's embedded credit risk component, requiring adjustments in pricing.

**Example: SOFR-Linked Loan**
```bash
Loan Terms:
Principal: $1,000,000
Rate: 30-day SOFR Average + 2% spread.
SOFR Calculation:
Suppose 30-day SOFR Average = 3%.
Loan rate = 3% + 2% = 5% annualized.
Interest Payment:
Monthly interest = (5%/12) × 1,000,000 = 4,166.67.
```

### What is a Swap?
A swap is a financial derivative contract in which two parties agree to exchange cash flows based on a specified notional amount over a defined period. The most common type is the interest rate swap, where one party exchanges fixed-rate cash flows for floating-rate cash flows (or vice versa).

#### Fixed vs. Floating USD Swap
In a fixed-to-floating USD interest rate swap, one party pays a fixed interest rate, and the other pays a floating interest rate (often tied to a benchmark like SOFR or LIBOR).

#### Key Terms:
- Notional Amount: The principal amount on which the interest payments are calculated. It is not exchanged.
- Fixed Rate: A predetermined interest rate agreed upon at the swap’s initiation.
- Floating Rate: A variable rate that resets periodically, based on a benchmark rate (e.g., SOFR or LIBOR).
- Maturity: The duration of the swap (e.g., 10 years).
- Payment Frequency: Commonly semi-annual for fixed payments and quarterly for floating payments.

```bash
Example: Fixed vs. Floating USD Swap
Scenario:
Notional Amount: $100 million.
Fixed Rate: 3% per year.
Floating Rate: 3-month SOFR (e.g., initially 2.5% but fluctuates quarterly).
Maturity: 10 years.
Fixed Payments: Semi-annual.
Floating Payments: Quarterly.

Cash Flows:
Party A (payer of fixed): Agrees to pay 3% annualized on the notional amount.
Party B (payer of floating): Agrees to pay the 3-month SOFR rate, which resets every 3 months.
```

- The first payment in an interest rate swap is typically exchanged after the first accrual period, not at the start of the swap. 
- The notional amount is only a reference for calculating payments; it is not exchanged.

#### Payment Schedule
Floating Leg (Quarterly):
- Payments are made every 3 months.
- The payment amount is based on the 3-month SOFR rate applied to the notional for the preceding 3-month period.
- Floating rates are typically set at the start of each period (using the SOFR observed at that time) and paid at the end of the period.

Fixed Leg (Semi-Annual):
- Payments are made every 6 months.
- The payment amount is based on the fixed interest rate agreed upon at the start of the swap.
- The fixed rate applies to the notional for the preceding 6-month period.

Rate Reset:
- At the start of each period (e.g., April 1), the applicable floating rate is observed and locked in. For a 3-month floating rate, this could be the 3-month SOFR rate published on April 1.
- This rate applies to the notional amount for the upcoming 3-month period (April 1 to July 1).

The fixed rate in an interest rate swap is determined at the outset of the swap contract. It is calculated to ensure that the present value (PV) of the fixed payments equals the PV of the expected floating payments over the life of the swap. This creates a "fair value" swap with no upfront payment between the parties.

#### Steps to Determine the Fixed Rate
Gather Inputs:
- Swap Notional Amount: The agreed principal amount for calculating interest payments.
- Floating Rate Curve: Forward rates derived from the current yield curve (e.g., SOFR forward rates).
- Discount Factor Curve: Derived from the risk-free rate or another benchmark, showing how future cash flows are discounted back to today.
- Swap Maturity: The length of the swap (e.g., 10 years).
- Payment Frequencies: Typically semi-annual for the fixed leg and quarterly for the floating leg.

Calculate the PV of Floating Payments:
- Use the forward rates from the floating rate curve for each period.
- Estimate floating cash flows using the forward rates for each period.
- Discount these cash flows to the present using the discount factor curve.

Set the Fixed Rate to Equalize PVs:
- Calculate the fixed cash flows, ensuring their PV equals the PV of the floating payments:
- Solve for the fixed rate (FixedRate) that balances PV-Floating = PV-FixedRate

