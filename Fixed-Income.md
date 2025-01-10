
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

### FedFunds vs SOFR
FedFunds is set by FOMC cmmittee of Fed Reserve.

| Aspect | Fed Funds Rate | SOFR |
| --- | --- | --- |
| **Type** | Unsecured (based on credit worthiness) | Secured by Treasury bills/bonds |
| **Market** | Federal funds market | Repo market |
| **Credit Risk** | Yes | No  |
| **Purpose** | Bank-to-bank overnight lending | Broad market benchmark |
| **Use Cases** | Fed policy rate, loans | LIBOR replacement, derivatives |

### ISDA vs Swap Dealers
- ISDA (International Swaps and Derivatives Association) is an important organization that provides standardized documentation and promotes sound risk management practices in the global derivatives market.
- Swap Dealers are key market participants that facilitate the trading of swaps and other derivative products by providing liquidity, acting as counterparties, and managing risks.

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

#### How an Interest Rate Swap is Used to Hedge FR Debt:

| **Step** | **Explanation** |
| --- | --- |
| **Hedge Objective** | Protect against rising interest rates on floating-rate debt |
| **Enter Swap** | Enter a swap to **pay a fixed rate** and **receive floating** |
| **Floating Debt Payments** | Still pay floating rates on the debt (e.g., LIBOR + spread) |
| **Fixed Swap Payments** | Pay a fixed rate on the swap |
| **Floating Swap Receipts** | Receive the floating rate on the swap, offsetting higher floating debt payments |
| **Result** | Convert floating debt into a more predictable, hedged fixed cost |

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

Bullet bonds: principal is paid at maturuty in **lump sum and no partial payment** is done; it is a single bond that is issued and principal paid at maturity. Bond holder recieves coupons periodically.
Term bond: A series of bonds are issued such as 10000 2$ 10y treasury bonds and they all **mature at same time**. Bond holder recieves coupons periodically.
Zero coupon: principal is paid at maturity; bond is issued at discount to account for interest rate.

Actually, bonds can be both bullet bonds and term bonds. The term "term bond" refers to the maturity structure of a bond issue, whereas the term "bullet bond" refers to the structure of how the principal is repaid.

| **Feature** | **Bill** | **Note** | **Bond** |
| --- | --- | --- | --- |
| **Maturity** | Short-term (up to 1 year) | Medium-term (1–10 years) | Long-term (more than 10 years) |
| **Interest** | Issued at a discount (no coupons) | Pays periodic coupons | Pays periodic coupons |
| **Issuer** | Governments, corporations | Governments, corporations | Governments, corporations, municipalities |
| **Common Examples** | Treasury bills (T-bills), commercial paper | Treasury notes (T-notes), corporate notes | Treasury bonds (T-bonds), corporate bonds |

**Bond pricing convention** refers to the standard methods and rules used to calculate the price of a bond in the financial markets. This includes how bond prices are quoted, how interest (coupon) payments are accounted for, and how to determine the bond's price based on its yield, maturity, and coupon rate. Here are the key components of bond pricing conventions:

### **1\. Price Quotation**

*   **Bond Price**: The price of a bond is typically quoted as a percentage of its **face value** (par value), which is usually **$1,000**.
*   **Example**: A bond priced at **98** means it is priced at **98% of its par value**, or $980. A bond priced at **102** means it is priced at **102% of its par value**, or $1,020.

### **2\. Accrued Interest**

*   **Accrued Interest** refers to the interest that has accumulated on a bond since the last coupon payment date, but has not yet been paid.
*   **Formula**: Accrued Interest\=Coupon Rate×Face Value×Days Since Last CouponDays in Coupon Period\\text{Accrued Interest} = \\frac{\\text{Coupon Rate} \\times \\text{Face Value} \\times \\text{Days Since Last Coupon}}{\\text{Days in Coupon Period}}Accrued Interest\=Days in Coupon PeriodCoupon Rate×Face Value×Days Since Last Coupon​
*   **Example**: If a bond pays an annual coupon of 6% on a $1,000 face value bond, the accrued interest for 90 days would be: 6%×1,000×90365\=14.79\\frac{6\\% \\times 1,000 \\times 90}{365} = 14.793656%×1,000×90​\=14.79 If the bond is bought between coupon payments, the buyer pays the seller the accrued interest in addition to the price of the bond.

### **3\. Clean vs. Dirty Price**

*   **Clean Price**: The price quoted for a bond **without** including the accrued interest.
    *   This is the standard way bonds are quoted in the market.
    *   For example, if a bond's price is quoted at 98, it means **98% of par**, and this is the clean price.
*   **Dirty Price**: The price of the bond **including the accrued interest**.
    
    *   If the clean price of a bond is 98, and there’s accrued interest of $14.79, the dirty price would be:
    
    Dirty Price\=Clean Price+Accrued Interest\=980+14.79\=994.79\\text{Dirty Price} = \\text{Clean Price} + \\text{Accrued Interest} = 980 + 14.79 = 994.79Dirty Price\=Clean Price+Accrued Interest\=980+14.79\=994.79

### **4\. Yield and Yield to Maturity (YTM)**

*   The price of a bond is directly related to its **yield**. The bond price changes to ensure that the bond’s yield matches the required return for an investor.
    *   **Yield to Maturity (YTM)**: The rate of return an investor will earn if the bond is held until maturity. YTM takes into account the bond's current market price, coupon payments, and the difference between the bond's face value and the price paid for the bond.
*   **Price Calculation**: The bond price is the **present value** of its future cash flows (coupons and principal repayment) discounted at the bond’s yield. P\=∑i\=1nC(1+YTM)i+F(1+YTM)nP = \\sum\_{i=1}^{n} \\frac{C}{(1 + YTM)^i} + \\frac{F}{(1 + YTM)^n}P\=i\=1∑n​(1+YTM)iC​+(1+YTM)nF​ Where:
    *   PPP = Price of the bond
    *   CCC = Coupon payment
    *   FFF = Face value of the bond
    *   YTMYTMYTM = Yield to maturity
    *   nnn = Number of periods (e.g., years or semi-annual periods)

### **5\. Day Count Conventions**

*   **Day Count Conventions** specify how the days between coupon periods are calculated for pricing purposes, as it impacts accrued interest.
*   Common conventions include:
    *   **Actual/Actual**: Uses the actual number of days in the month/year.
    *   **30/360**: Assumes 30 days per month and 360 days per year.
    *   **Actual/360**: Uses the actual number of days in the period, but assumes a 360-day year.
    *   **30/365**: Assumes 30 days per month and 365 days per year.

### **6\. Price-Yield Relationship**

*   Bond prices and yields have an **inverse relationship**:
    *   When **interest rates rise**, bond prices fall.
    *   When **interest rates fall**, bond prices rise.

### **7\. Premium vs. Discount Bonds**

*   **Premium Bond**: A bond priced above its face value (i.e., above 100% of par). This usually happens when the bond’s coupon rate is higher than current market rates.
*   **Discount Bond**: A bond priced below its face value (i.e., below 100% of par). This occurs when the bond’s coupon rate is lower than the market interest rates.

- - -

### **Summary of Key Bond Pricing Conventions:**

| **Concept** | **Explanation** |
| --- | --- |
| **Price Quotation** | Bonds are quoted as a percentage of par value (usually $1,000). |
| **Accrued Interest** | The interest accumulated since the last coupon payment is added to the price when purchasing the bond. |
| **Clean Price** | The price of the bond excluding accrued interest. |
| **Dirty Price** | The price of the bond including accrued interest. |
| **Yield and YTM** | Bond price is the present value of future cash flows, and the yield adjusts to match market conditions. |
| **Day Count Conventions** | Rules used to calculate the number of days for accrued interest (e.g., 30/360, Actual/Actual). |
| **Premium/Discount** | Premium bonds are priced above par, discount bonds are priced below par. |

**Bond duration** is a measure of the **interest rate sensitivity** of a bond or a bond portfolio. It represents the **weighted average time** it takes for a bond’s cash flows (coupons and principal repayments) to be repaid, and it helps investors assess how much a bond’s price will change in response to changes in interest rates.

### **Key Concepts of Bond Duration:**

1.  **Duration as a Risk Measure**:
    
    *   Duration quantifies how much the price of a bond will change with a **1% change in interest rates**.
    *   A **longer duration** implies that the bond’s price is more sensitive to interest rate changes, while a **shorter duration** means the bond’s price is less sensitive.
2.  **Types of Duration**:
    
    *   **Macaulay Duration**: The weighted average time to receive the bond’s cash flows. It is expressed in years.
    *   **Modified Duration**: A more practical measure that reflects the percentage change in the bond price for a 1% change in interest rates. It is derived from the Macaulay duration and gives a better indication of price sensitivity to interest rate changes.

### **Formula for Macaulay Duration**:

The **Macaulay duration** can be calculated using the following formula:

D\=∑t\=1Tt×C(1+y)t+T×M(1+y)T∑t\=1TC(1+y)t+M(1+y)TD = \\frac{ \\sum\_{t=1}^{T} \\frac{t \\times C}{(1 + y)^t} + \\frac{T \\times M}{(1 + y)^T} }{ \\sum\_{t=1}^{T} \\frac{C}{(1 + y)^t} + \\frac{M}{(1 + y)^T} }D\=∑t\=1T​(1+y)tC​+(1+y)TM​∑t\=1T​(1+y)tt×C​+(1+y)TT×M​​

Where:

*   DDD = Duration (in years)
*   CCC = Coupon payment
*   MMM = Maturity value (face value)
*   yyy = Yield to maturity (YTM)
*   ttt = Time period (in years)
*   TTT = Total number of periods (years to maturity)

### **Formula for Modified Duration**:

The **Modified duration** is derived from the Macaulay duration and can be calculated as:

Dmod\=Dmac(1+y/n)D\_{mod} = \\frac{D\_{mac}}{(1 + y/n)}Dmod​\=(1+y/n)Dmac​​

Where:

*   DmodD\_{mod}Dmod​ = Modified duration
*   DmacD\_{mac}Dmac​ = Macaulay duration
*   yyy = Yield to maturity (YTM)
*   nnn = Number of compounding periods per year

### **Interpretation**:

*   If a bond has a **modified duration of 5**, it means that for every **1% change in interest rates**, the bond’s price will move in the **opposite direction** by approximately **5%**. If interest rates go up by 1%, the bond price will decrease by around 5%, and if interest rates fall by 1%, the bond price will increase by about 5%.
    
*   **Longer duration bonds** (such as long-term bonds) are more sensitive to interest rate changes than **shorter duration bonds** (such as short-term bonds).
    

### **Factors Influencing Bond Duration**:

1.  **Coupon Rate**:
    *   **Higher coupon bonds** tend to have **shorter durations** because the investor receives more cash flow early on, reducing the weighted average time to receive payments.
    *   **Lower coupon bonds** (or zero-coupon bonds) tend to have **longer durations** because the bondholder receives most of the cash flow at maturity.
2.  **Time to Maturity**:
    *   **Bonds with longer maturities** tend to have **longer durations** because the principal repayment is further in the future, increasing the weighted average time.
3.  **Yield to Maturity (YTM)**:
    *   **Higher YTM** generally reduces the duration because higher discount rates lower the present value of future cash flows, shortening the time it takes to recoup the bond's price.

### **Example**:

Let's consider a bond with:

*   A **$1,000 face value**,
*   A **5% coupon rate** (annual coupon),
*   A **10-year maturity**,
*   A **YTM of 6%**.

By calculating the bond's duration (either Macaulay or modified), we can determine the sensitivity of the bond's price to changes in interest rates. If the bond’s **modified duration** is 7 years, then a **1% increase in interest rates** would result in an approximate **7% decline in the bond's price**.

### **Why is Duration Important?**:

*   **Interest Rate Risk Management**: Duration helps investors understand how much risk they are taking in terms of price fluctuations due to interest rate changes.
*   **Immunization**: Bond portfolios with a **duration matching the investor's investment horizon** can be used to **immunize** against interest rate risk, ensuring a more predictable return.
*   **Portfolio Construction**: Duration is often used by fixed-income portfolio managers to align the portfolio’s interest rate sensitivity with the investor’s goals and risk tolerance.

### **Summary**:

| **Duration Type** | **Description** |
| --- | --- |
| **Macaulay Duration** | Weighted average time to receive cash flows. |
| **Modified Duration** | Measures price sensitivity to interest rate changes. |
| **Longer Duration** | More price sensitivity to interest rate changes. |
| **Shorter Duration** | Less price sensitivity to interest rate changes. |

Duration is a key concept for understanding bond price fluctuations in response to interest rate changes and for managing interest rate risk effectively.


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
| **Delta (Δ)** | Sensitivity to changes in underlying stock price by $1. A delta of 0.5 means that for every $1 increase in the stock price, the call option’s price will increase by $0.50. | For calls: increases as stock price rises; For puts: decreases as stock price rises | Calls (positive) |
| **Gamma (Γ)** | Sensitivity of delta to changes in underlying stock price | High gamma = faster changes in delta for small price changes | Both calls and puts (higher near ATM) |
| **Theta (Θ)** | Sensitivity to time decay. If theta is -0.05, the option’s value will decrease by $0.05 per day due to time decay. | Negative for long options; options lose value as expiration nears | Both calls and puts |
| **Vega (ν)** | Sensitivity to changes in volatility by 1%. A vega of 0.10 means that for every 1% increase in volatility, the option’s price will increase by $0.10. | Higher volatility increases option price | Both calls and puts (positive) |
| **Rho (ρ)** | Sensitivity to changes in risk-free interest rates for 1% change. A rho of 0.20 means that if interest rates increase by 1%, the price of the call option will increase by $0.20.| Calls rise with interest rates; Puts fall with interest rates | Calls (positive) |


### Black-Scholes Model
The Black-Scholes formula calculates the fair market value of an option by taking into account the current stock price, the option's strike price, the time to expiration, the volatility of the underlying asset, and the risk-free interest rate.

The Black-Scholes model is a cornerstone in modern financial markets, particularly for pricing European-style options. Despite its assumptions and limitations, it provides a closed-form solution for option pricing, offering insight into how factors such as stock price, strike price, time, volatility, and interest rates interact to determine option value.

### **Limitations of the Black-Scholes Model:**

1.  **Constant volatility assumption**: In reality, volatility is not constant over time. It fluctuates based on market conditions.
2.  **European-style options**: The model is designed for options that can only be exercised at expiration. It does not apply to American-style options, which can be exercised at any time before expiration.
3.  **No dividends**: The Black-Scholes model assumes that the underlying asset does not pay dividends. However, in practice, many stocks pay dividends, and this can significantly affect the option's price.
4.  **No transaction costs**: The model assumes that there are no transaction fees or taxes, which may not reflect real-world conditions.
5.  **Efficient market assumption**: The model assumes that markets are efficient, meaning that there are no arbitrage opportunities. In reality, markets can be inefficient, and arbitrage opportunities may exist.

**Implied Volatility:** In practice, market participants often calculate implied volatility, which is the volatility figure that makes the Black-Scholes formula match the market price of the option.

#### Volatility Smile
The volatility smile refers to the shape of a graph that shows implied volatility (IV) for options with the same expiration date but different strike prices. In a volatility smile, implied volatility tends to be higher for deep out-of-the-money (OTM) and deep in-the-money (ITM) options and lower for at-the-money (ATM) options.

#### Volatility Skew
The volatility skew (also called volatility slope) refers to the tendency of implied volatility to vary with the strike price in a way that does not form a smile but instead shows a sloping pattern. This occurs when implied volatility is higher on one side of the strike. Whichever way the smile is skewing, U/L price is likely to move in that direction.


### An Eurodollar (ED) future - provides Liquidity, Leveraging and Hedging
An Eurodollar (ED) future is a financial contract that represents a bet on the future value of U.S. dollar interest rates. It specifically tracks the three-month U.S. dollar LIBOR (London Interbank Offered Rate), which is the interest rate at which banks lend to each other in U.S. dollars in the international interbank market.

Eurodollar futures are one of the most widely traded futures contracts in the world and are used primarily by institutional investors, hedgers, and traders to manage interest rate risk or to speculate on future interest rate movements.

Example of Eurodollar Future:
- Suppose an investor is looking to hedge against the possibility that interest rates might rise in the near future. They might buy a Eurodollar futures contract at a price of 98.50 (which implies a LIBOR rate of 1.50%).
- If the LIBOR rate increases by 0.25% to 1.75% by the time the contract expires, the price of the futures contract will fall (to 98.25), and the investor can sell the contract for a loss.

**Eurodollar (ED) futures** are still actively traded, but there has been a significant shift toward trading **SOFR futures** due to the transition away from LIBOR.

### **Background: Transition from LIBOR to SOFR**

*   The **LIBOR (London Interbank Offered Rate)**, which was the reference rate used for Eurodollar futures, has been gradually phased out. This decision came after **regulatory concerns** regarding LIBOR's reliability and manipulation risks. As a result, the **U.S. Federal Reserve** and other regulators introduced **SOFR (Secured Overnight Financing Rate)** as a replacement benchmark for U.S. dollar-based interest rates.

### **Eurodollar Futures vs SOFR Futures**:

1.  **Eurodollar Futures**:
    
    *   These futures contracts are based on the **three-month LIBOR** rate.
    *   Eurodollar futures are still actively traded on exchanges like the **CME Group** and are widely used by market participants, especially for hedging and speculating on U.S. short-term interest rates.
2.  **SOFR Futures**:
    
    *   **SOFR futures** are newer contracts introduced to replace Eurodollar futures as the market moves away from LIBOR-based products.
    *   These futures are based on the **SOFR rate**, which is a transaction-based, overnight, secured rate derived from the U.S. Treasury repurchase agreements market. SOFR is considered more robust and transparent compared to LIBOR.
    *   **SOFR futures** are also traded on the **CME Group** and serve a similar purpose to Eurodollar futures, such as managing short-term interest rate exposure or hedging future rate movements.

### **Current Status**:

*   **Eurodollar futures** are still actively traded for legacy contracts but no new ones are issued, while **SOFR futures** are gaining prominence as the market transitions to the new benchmark.
*   The **transition from LIBOR to SOFR** is being driven by financial regulators, and over time, **SOFR futures** are expected to replace Eurodollar futures for most market participants.

### **Differences Between Eurodollar Futures and SOFR Futures**:

| **Feature** | **Eurodollar Futures** | **SOFR Futures** |
| --- | --- | --- |
| **Underlying Rate** | Three-month LIBOR | 30 days average SOFR (Secured Overnight Financing Rate) |
| **Settlement** | Cash-settled based on LIBOR rate for the contract month | Cash-settled based on SOFR rate for the contract month |
| **Market Usage** | Hedging, Speculation on LIBOR rates | Hedging, Speculation on short-term interest rates based on SOFR |
| **Liquidity** | Highly liquid, still widely traded | Growing liquidity, particularly in post-LIBOR markets |
| **Transition** | Gradually being replaced by SOFR futures | Gaining adoption as the primary benchmark for U.S. dollar rates |
| **Expiration** | Quarterly and monthly expirations | Quarterly and monthly expirations |

### **Which Futures Should You Use?**

*   **Eurodollar futures** are still widely used in the market for legacy reasons, especially by those who want to hedge or speculate on LIBOR-based products or existing legacy LIBOR contracts.
*   **SOFR futures** are becoming the standard as financial markets move away from LIBOR. These futures are expected to be the main vehicle for hedging and speculation on U.S. interest rates going forward, particularly as more products and derivatives transition to SOFR.

The CME Group has ceased issuing new Eurodollar futures contracts for most maturities following the transition away from LIBOR. This shift is part of the broader move away from the LIBOR benchmark to the SOFR benchmark, as LIBOR is being phased out due to concerns over its reliability and manipulation risks.

### Rate Curves
**Rate curves**, such as yield curves or discount curves, are constructed using observable market data to represent the relationship between interest rates and various maturities. These curves are fundamental tools in pricing, risk management, and financial analysis.

Here’s a step-by-step explanation of how rate curves are typically built:

- - -

### **1\. Collect Market Data**

The first step involves gathering market instruments that reflect interest rates at different maturities. Commonly used instruments include:

*   **Overnight Index Rates (OIS):** Short-term rates for overnight borrowing.
*   **Deposits:** Spot rates for very short maturities (e.g., 1M, 3M).
*   **Futures:** Implied rates from instruments like Eurodollar or SOFR futures for intermediate maturities.
*   **Swaps:** Interest rate swap rates for longer maturities.
*   **Bonds:** Yields from government or corporate bonds.

- - -

### **2\. Choose a Bootstrapping Method**

The curve is constructed through **bootstrapping**, which sequentially determines zero-coupon rates for different maturities. This involves:

*   Using known rates for short maturities (e.g., deposit rates).
*   Inferring rates for intermediate and long maturities by solving for discount factors.

- - -

### **3\. Calculate Discount Factors**

For each maturity, calculate a **discount factor**, which represents the present value of $1 received at that maturity:

D(T)\=1(1+r(T))TD(T) = \\frac{1}{(1 + r(T))^T}D(T)\=(1+r(T))T1​

Where:

*   r(T)r(T)r(T): The rate for maturity TTT.
*   D(T)D(T)D(T): The discount factor for maturity TTT.

- - -

### **4\. Construct the Short End of the Curve**

*   **Overnight and Spot Rates:** Use OIS or deposit rates for maturities up to 1 year.
*   These rates are directly input into the curve since they are relatively straightforward.

- - -

### **5\. Extend to Intermediate Maturities**

*   **Futures:** Extract implied forward rates from interest rate futures.
*   **Calculation:** If the futures price is PPP, the implied rate is: r\=100−Pr = 100 - Pr\=100−P
*   The forward rate is used to derive discount factors for maturities aligned with futures contracts.

- - -

### **6\. Build the Long End of the Curve**

*   **Swaps or Bonds:** Use swap rates or bond yields for maturities longer than those covered by futures.
*   Solve for the zero-coupon rates that match the market prices of these instruments using the previously calculated discount factors.

- - -

### **7\. Interpolate Missing Points**

*   Use interpolation techniques to fill in rates for maturities not directly observable in the market.
*   Common methods:
    *   **Linear Interpolation**: Straight-line interpolation between two known rates.
    *   **Cubic Spline**: A smoother curve-fitting method.
    *   **Piecewise Constant Forward Rates**: Ensures consistency in forward rates.

- - -

### **8\. Validate the Curve**

*   Check for arbitrage opportunities by ensuring the curve is smooth and free of inconsistencies.
*   Validate that the derived discount factors and forward rates align with market instrument prices.

- - -

### **Example: Building a Discount Curve**

1.  **Input Data**:
    
    *   1M deposit rate: 2.00%
    *   3M deposit rate: 2.50%
    *   6M futures-implied rate: 2.75%
    *   1Y swap rate: 3.00%
2.  **Construct Zero-Coupon Rates**:
    
    *   Use deposit rates directly for 1M and 3M.
    *   Bootstrap 6M and 1Y rates using futures and swaps.
3.  **Interpolate**:
    
    *   Fill in intermediate maturities (e.g., 2M, 4M) using interpolation.

- - -

### **Applications of Rate Curves**

*   **Pricing:** Discount cash flows for bonds, swaps, or derivatives.
*   **Risk Management:** Measure sensitivities like duration or convexity.
*   **Hedging:** Derive forward rates to manage interest rate exposure.
*   **Market Analysis:** Understand economic expectations (e.g., steepening or flattening yield curves).
