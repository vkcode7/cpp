
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

### Capital Markets
**Capital Markets** are financial markets where long-term debt and equity instruments are traded. These markets enable businesses, governments, and institutions to raise funds for investments, operations, or expansions, and they allow investors to invest in financial assets for potential returns.

### **Key Components of Capital Markets**

1.  **Types of Instruments**:
    
    *   **Equity Instruments**: Stocks or shares that represent ownership in a company.
    *   **Debt Instruments**: Bonds, debentures, or other fixed-income securities that represent a loan made by an investor to a borrower.
2.  **Participants**:
    
    *   **Issuers**: Companies, governments, or other entities that raise funds by issuing stocks or bonds.
    *   **Investors**: Individuals, institutional investors (e.g., mutual funds, pension funds), or hedge funds that invest in these instruments.
    *   **Intermediaries**: Investment banks, brokers, and dealers that facilitate transactions.
3.  **Markets**:
    
    *   **Primary Market**: Where new securities are issued and sold for the first time (e.g., IPOs or new bond issuances).
    *   **Secondary Market**: Where existing securities are traded between investors (e.g., stock exchanges like NYSE or NASDAQ).
4.  **Regulators**:
    
    *   Regulatory bodies oversee and ensure transparency and fairness in the markets (e.g., the **Securities and Exchange Commission (SEC)** in the U.S.).

- - -

### **Functions of Capital Markets**

1.  **Raising Capital**: Companies and governments can issue bonds or stocks to raise funds for projects and operations.
2.  **Price Discovery**: Markets determine the fair value of securities based on supply and demand.
3.  **Liquidity**: Investors can buy and sell securities, converting them into cash when needed.
4.  **Risk Management**: Derivatives in capital markets allow participants to hedge against risks like interest rate changes or currency fluctuations.

- - -

### **Types of Capital Markets**

1.  **Stock Markets**:
    
    *   Facilitate trading of equity instruments (e.g., common and preferred shares).
    *   Example: NYSE, NASDAQ.
2.  **Bond Markets**:
    
    *   Allow trading of fixed-income securities like government bonds, corporate bonds, and municipal bonds.
    *   Example: U.S. Treasury market.
3.  **Foreign Exchange Markets**:
    
    *   Facilitate currency trading and are crucial for cross-border capital flows.
4.  **Derivatives Markets**:
    
    *   Instruments like options, futures, and swaps derived from underlying assets.
5.  **Commodities Markets**:
    
    *   Trading of physical goods or commodity-linked financial instruments.

### **Role in the Economy**

1.  **Economic Growth**: Facilitates efficient allocation of capital, supporting economic expansion.
2.  **Wealth Creation**: Offers investment opportunities for wealth accumulation.
3.  **Corporate Governance**: Publicly traded companies are subject to scrutiny, promoting transparency and accountability.


### Yield Auctions
**Yield auctions** are a type of auction used by governments or institutions to sell debt securities, such as Treasury bonds, bills, or notes, to investors. In these auctions, the bidders specify the **yield** (or return) they are willing to accept rather than the price they are willing to pay for the security.

### **Example of a Yield Auction**

#### **Treasury Auction**

*   The U.S. Treasury uses yield auctions to issue bonds.
*   Suppose the Treasury wants to issue $10 billion in 10-year notes:
    1.  **Investors Submit Bids**:
        *   Investor A: Bids a yield of 3.00%.
        *   Investor B: Bids a yield of 3.10%.
        *   Investor C: Bids a yield of 3.20%.
    2.  **Treasury Sets a Cutoff Yield**:
        *   The Treasury accepts bids up to the 3.10% yield to raise the required $10 billion.
    3.  **Pricing**:
        *   In a **uniform price auction**, all winning bidders receive the securities at the same price, corresponding to the 3.10% yield.
        *   In a **multiple price auction**, each bidder pays a price based on their individual yield.

### **Advantages of Yield Auctions**

1.  **Efficient Pricing**: Yield auctions let the market determine the price and interest rate of the securities.
2.  **Transparency**: Competitive bidding ensures fairness and market-driven outcomes.
3.  **Broad Participation**: Institutional and retail investors can participate in auctions.


### Financial intermediaries and institutions
Financial intermediaries and institutions play a critical role in secondary markets, where previously issued financial securities (e.g., stocks, bonds, derivatives) are traded between investors. Their role is central to providing liquidity, enabling price discovery, and ensuring market efficiency.

Role of **financial intermediaries and institutions** in **secondary markets** in a tabular format:

| **Role** | **Description** | **Example Institutions** |
| --- | --- | --- |
| **Liquidity Providers** | Ensure securities can be bought or sold easily, creating a continuous market. | Market Makers (Investment Banks, Broker-Dealers), Brokerage Firms |
| **Price Discovery** | Help determine the fair market value of securities through active trading. | Exchanges (NYSE, NASDAQ), Asset Managers, Hedge Funds |
| **Market Efficiency** | Facilitate smooth operations by matching buyers and sellers and minimizing price distortions. | Asset Managers, Hedge Funds, Brokers |
| **Risk Management** | Use secondary markets for hedging and diversification to manage portfolio risks. | Hedge Funds, Insurance Companies, Asset Managers |
| **Access to Capital** | Provide liquidity to attract investors and enable easy buying/selling of securities. | Mutual Funds, Pension Funds, Investment Banks |
| **Investor Confidence** | Ensure transparency, fairness, and regulatory compliance in trading activities. | Regulated Exchanges (NYSE, NASDAQ), Broker-Dealers |

### Bond
A bond is a debt security that represents a loan made by an investor (the bondholder) to a borrower (usually a corporation, government, or municipality). In return for the loan, the issuer of the bond agrees to make periodic interest payments (called coupons) to the bondholder and repay the principal (face value) of the bond at maturity.

Key features are Issuer, Face Value, Coupon Rate and Payment frequency, Maturity date and Issuer rating

#### Bond Risks

| **Risk** | **Description** | **Impact** |
| --- | --- | --- |
| **Interest Rate Risk** | Risk of bond prices falling due to rising interest rates. | Longer-duration bonds are more sensitive to interest rate changes. |
| **Credit Risk** | Risk that the issuer will default on its payments or be unable to meet obligations. | Can lead to partial or complete loss of principal and interest. |
| **Inflation Risk** | Risk that inflation erodes the purchasing power of bond interest payments. | Bonds with fixed interest payments lose real value during inflation. |
| **Liquidity Risk** | Risk that the bond cannot be sold quickly without affecting its price. | Can result in lower prices and difficulty in executing trades. |
| **Call Risk** | Risk that the issuer may call (redeem) the bond before maturity, often when interest rates decline. | Investors may be forced to reinvest at lower rates. |
| **Reinvestment Risk** | Risk that cash flows (coupon payments or principal) are reinvested at lower rates. | Reduces the expected return if reinvestment rates fall. |
| **Currency Risk** | Risk that exchange rate fluctuations impact the value of bonds in foreign currencies. | Affects bonds issued in foreign currencies or by foreign issuers. |
| **Duration Risk** | Risk related to the bond’s sensitivity to interest rate changes, influenced by its maturity, coupon rate, and yield. | Longer duration bonds are more affected by interest rate changes. |
| **Event Risk** | Risk that unexpected events (e.g., mergers, acquisitions, natural disasters) affect the issuer’s ability to pay. | Can negatively impact the issuer’s creditworthiness and bond prices. |

#### Bond Pricing
The price of a bond is determined by calculating the present value of its future cash flows, which include the periodic interest payments (coupons) and the principal repayment at maturity. The bond price is the sum of the present values of these future payments, discounted at the market interest rate (or the bond's yield).

Factors that affect a bond price is - interest rate, credit rating, time to maturity and coupon rate

#### Bond Yield
A bond yield is the return an investor can expect to earn from a bond over a specific period, typically expressed as an annual percentage rate. It reflects the income (interest) an investor receives relative to the bond’s price, and it can vary depending on the bond’s type, price, maturity, and prevailing market conditions.

YTM: You can think of Yield to Maturity (YTM) as the single discount rate that equates the present value (PV) of all future cash flows (coupon payments and the face value to be repaid at maturity) to the current price (market price) of the bond

- If the bond price is below par (at a discount), the YTM will be higher than the coupon rate.
- If the bond price is above par (at a premium), the YTM will be lower than the coupon rate.

In other words, YTM is the rate that makes the sum of the discounted cash flows equal to the bond’s current market price.

There are several types of **bond yields** that investors use to assess the profitability and risk associated with bonds. Below is a summary of the key types of bond yields:

| **Type of Yield** | **Definition** | **Formula** (if applicable) | **Purpose/Usage** |
| --- | --- | --- | --- |
| **Coupon Yield (Nominal Yield)** | The bond's annual coupon payment divided by its face value (par value). | Coupon Yield\=Coupon PaymentFace Value\\text{Coupon Yield} = \\frac{\\text{Coupon Payment}}{\\text{Face Value}}Coupon Yield\=Face ValueCoupon Payment​ | Measures the bond's fixed interest return relative to its face value. |
| **Current Yield** | The bond's annual coupon payment divided by its current market price. | Current Yield\=Coupon PaymentCurrent Market Price\\text{Current Yield} = \\frac{\\text{Coupon Payment}}{\\text{Current Market Price}}Current Yield\=Current Market PriceCoupon Payment​ | Provides a measure of income relative to the current price of the bond. |
| **Yield to Maturity (YTM)** | The total return an investor can expect to earn if the bond is held until maturity. It includes coupon payments and the difference between the purchase price and face value. | YTM\=Solve for r in ∑t\=1TC(1+r)t+F(1+r)T\=Price of Bond\\text{YTM} = \\text{Solve for } r \\text{ in } \\sum\_{t=1}^{T} \\frac{C}{(1 + r)^t} + \\frac{F}{(1 + r)^T} = \\text{Price of Bond}YTM\=Solve for r in ∑t\=1T​(1+r)tC​+(1+r)TF​\=Price of Bond | Assesses the long-term return, assuming the bond is held to maturity and all payments are made. |
| **Yield to Call (YTC)** | The total return an investor can expect to earn if the bond is called (redeemed early) by the issuer before the maturity date. | Similar to YTM, but assumes the bond is called at the earliest possible date. | Used for callable bonds, which can be redeemed by the issuer before maturity. |
| **Yield to Worst (YTW)** | The lowest yield an investor can receive if the bond is called or matures early. | Takes the minimum of YTM or YTC, whichever is less. | Provides a conservative estimate of yield, assuming the worst-case scenario. |
| **Yield to Put (YTP)** | The yield an investor will receive if the bond is put (sold back) to the issuer at the earliest possible date. | Similar to YTM, but assumes the bond is sold back to the issuer before maturity. | Relevant for bonds with a put option, where the holder can sell the bond back to the issuer. |
| **Yield to Taxable Equivalent** | The yield an investor would need from a taxable bond to match the yield of a tax-exempt bond, considering tax implications. | Yield to Taxable Equivalent\=Tax-Exempt Yield1−Tax Rate\\text{Yield to Taxable Equivalent} = \\frac{\\text{Tax-Exempt Yield}}{1 - \\text{Tax Rate}}Yield to Taxable Equivalent\=1−Tax RateTax-Exempt Yield​ | Used to compare taxable and tax-exempt bonds, particularly for investors in high tax brackets. |
| **Real Yield** | The yield on a bond adjusted for inflation, reflecting the actual purchasing power of the bond’s return. | Real Yield\=1+Nominal Yield1+Inflation Rate−1\\text{Real Yield} = \\frac{1 + \\text{Nominal Yield}}{1 + \\text{Inflation Rate}} - 1Real Yield\=1+Inflation Rate1+Nominal Yield​−1 | Measures the actual return after accounting for inflation. |
| **Yield to Maturity (YTM) for a Zero-Coupon Bond** | For zero-coupon bonds, YTM represents the discount rate that equates the bond's price to its face value. | YTM\=Face ValuePrice1T−1\\text{YTM} = \\frac{\\text{Face Value}}{\\text{Price}}^{\\frac{1}{T}} - 1YTM\=PriceFace Value​T1​−1 | Applies to zero-coupon bonds, which do not make periodic interest payments but are sold at a discount. |


### Derivatives
A derivative is a financial instrument whose value is derived from the price or value of an underlying asset, index, or other financial instrument. Derivatives are essentially contracts between two or more parties, and their price or payoff is linked to the performance of the underlying asset.

### **Summary of Derivatives Types:**

| Type | Definition | Key Use Cases | Example |
| --- | --- | --- | --- |
| **Forward Contracts** | Customized agreement to buy/sell an asset in the future at a specified price. | Hedging, locking in future prices. | Currency forward contract for importers. |
| **Futures Contracts** | Standardized contract to buy/sell an asset on an exchange at a future date. | Hedging, speculation, portfolio management. | Crude oil futures contract. |
| **Options** | Right to buy/sell an asset at a specified price within a specific time frame. | Hedging, speculation, income generation. | Stock call option. |
| **Swaps** | Exchange of cash flows based on specified terms, such as interest rates or currencies. | Hedging interest rate risk, credit risk. | Interest rate swap to convert floating to fixed payments. |
| **Credit Derivatives** | Instruments to manage credit risk, like CDS. | Hedging against default, credit events. | Credit Default Swap (CDS). |
| **Warrants** | Long-term options to buy stock at a specific price. | Capital raising, hedging. | Warrant attached to a bond issue. |
| **Swaptions** | Option to enter into an interest rate swap. | Hedging interest rate changes. | Payer swaption to hedge rising rates. |
| **Commodity Derivatives** | Derivatives based on the price of commodities. | Hedging commodity price risk. | Wheat futures to hedge agricultural risk. |

### **Swaps**

*   **Definition**: A swap is a **contract** in which two parties agree to exchange cash flows or assets based on certain conditions (usually at regular intervals).
*   **Key Types**:
    *   **Interest Rate Swap**: Exchange fixed-rate payments for floating-rate payments or vice versa, often used to hedge interest rate risk.
    *   **Currency Swap**: Exchange cash flows in one currency for cash flows in another currency.
    *   **Commodity Swap**: Exchange cash flows based on commodity prices (e.g., oil, gold).
    *   **Credit Default Swap (CDS)**: A contract that allows one party to buy protection against the default of a bond or loan issuer.
*   **Example**: A company with floating-rate debt may enter into an **interest rate swap** to convert the floating payments into fixed payments, mitigating the risk of rising interest rates.

### **Credit Derivatives**

*   **Definition**: Credit derivatives are financial instruments used to manage credit risk by allowing parties to hedge or take on exposure to credit events (like default or credit downgrades).
*   **Key Types**:
    *   **Credit Default Swap (CDS)**: A contract that allows one party to buy protection against the default of a bond or loan issuer, while the seller assumes the default risk.
    *   **Total Return Swap (TRS)**: Involves the exchange of the total return on a bond or other asset, including income and capital appreciation, for fixed or floating rate payments.
*   **Example**: A CDS buyer may make periodic payments in exchange for protection against a bond issuer defaulting on its debt.

### **Warrants**

*   **Definition**: A **warrant** is a financial instrument that gives the holder the right to buy the underlying asset (usually stock) at a specific price (exercise price) before a certain expiration date.
*   **Key Characteristics**:
    *   **Issued by companies**: Often issued alongside bonds or preferred stocks to enhance the attractiveness of the issuance.
    *   **Long-term options**: Usually have a longer life than standard options (years instead of months).
    *   Similar to **call options**, but typically issued by the company itself and often with lower premiums.
*   **Example**: A company issues warrants alongside a bond, allowing the holder to purchase the company’s stock at a specified price in the future.

### **Swaptions**

*   **Definition**: A **swaption** is an option to enter into an interest rate swap, providing the buyer the right (but not the obligation) to enter into an interest rate swap at a specified future date.
*   **Key Characteristics**:
    *   Used to hedge or speculate on future interest rate changes.
    *   Two types: **payer swaption** (right to enter a swap where you pay fixed and receive floating) and **receiver swaption** (right to enter a swap where you receive fixed and pay floating).
*   **Example**: A company might buy a payer swaption to protect against the risk of rising interest rates.

### Cost to Carry
The cost of carry represents the total cost of holding an asset over time, factoring in financing costs, storage fees, insurance, opportunity costs and any potential income (dividends) from the asset. 

Cost of Carry = Futures Price − Spot Price

### Equity Options Determinants
The price of an equity option is influenced by several key determinants, which are commonly referred to as the "Greeks" and other market factors. These factors play a crucial role in determining the value and pricing of an option.

### **Summary of the Key Determinants of Equity Option Pricing**

| **Determinant** | **Impact on Option Price** |
| --- | --- |
| **Underlying Stock Price** | Call options increase in value as the stock price rises; Put options increase in value as the stock price falls. |
| **Strike Price** | A lower strike price increases the value of a call; A higher strike price increases the value of a put. |
| **Time to Expiration** | Longer time to expiration increases the value of options (more time for price movement). |
| **Volatility (σ)** | Higher volatility increases the value of both call and put options. |
| **Risk-Free Interest Rate (r)** | Higher rates increase the value of call options; decrease the value of put options. |
| **Dividends (D)** | Dividends decrease the value of call options and increase the value of put options. |
| **Option Type (Call vs. Put)** | Calls increase in value when stock price rises; Puts increase in value when stock price falls. |

### **Equity Options Greeks:**
The **Greeks** are a set of risk measures that describe how the price of an option is expected to change in response to various factors such as changes in the price of the underlying asset, time to expiration, volatility, and interest rates. Each Greek measures the sensitivity of an option’s price to a specific factor. Here's a breakdown of the key **Greeks** for equity options:

| **Greek** | **Measures** | **Impact on Option Price** | **Positive for** |
| --- | --- | --- | --- |
| **Delta (Δ)** | Sensitivity to changes in underlying stock price by $1 | For calls: increases as stock price rises; For puts: decreases as stock price rises | Calls (positive) |
| **Gamma (Γ)** | Sensitivity of delta to changes in underlying stock price | High gamma = faster changes in delta for small price changes | Both calls and puts (higher near ATM) |
| **Theta (Θ)** | Sensitivity to time decay | Negative for long options; options lose value as expiration nears | Both calls and puts |
| **Vega (ν)** | Sensitivity to changes in volatility | Higher volatility increases option price | Both calls and puts (positive) |
| **Rho (ρ)** | Sensitivity to changes in risk-free interest rates | Calls rise with interest rates; Puts fall with interest rates | Calls (positive) |
