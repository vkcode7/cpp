# Delivery Framework
Delivery framework is a sequence of steps and timings.
<img src="../assets/DeliveryFramework.png" width="50%">

## Requirements (~5 minutes)
The goal of the requirements section is to get a clear understanding of the system that you are being asked to design. To do this, we suggest you break your requirements into two sections.

### 1) Functional Requirements
Functional requirements are your "Users/Clients should be able to..." statements. These are the core features of your system and should be the first thing you discuss with your interviewer. 

For example, if you were designing a system like Twitter, you might have the following functional requirements:
- Users should be able to post tweets
- Users should be able to follow other users
- Users should be able to see tweets from users they follow

### 2) Non-functional Requirements
Non-functional requirements are statements about the system qualities that are important to your users. These can be phrased as "The system should be able to..." or "The system should be..." statements.

For example, if you were designing a system like Twitter, you might have the following non-functional requirements:
- The system should be highly availability, prioritizing availability over consistency
- The system should be able to scale to support 100M+ DAUs
- The system should be low latency, rendering feeds in under 200ms

Here is a checklist of things to consider that might help you identify the most important non-functional requirements for your system. You'll want to identify the top 3-5 that are most relevant to your system.
- CAP Theorem: Should your system prioritize consistency or availability? Note, partition tolerance is a given in distributed systems.
- Environment Constraints: Are there any constraints on the environment in which your system will run? For example, are you running on a mobile device with limited battery life? Running on devices with limited memory or limited bandwidth (e.g. streaming video on 3G)?
- Scalability: All systems need to scale, but does this system have unique scaling requirements? For example, does it have bursty traffic at a specific time of day? Are there events, like holidays, that will cause a significant increase in traffic? Also consider the read vs write ratio here. Does your system need to scale reads or writes more?
- Latency: How quickly does the system need to respond to user requests? Specifically consider any requests that require meaningful computation. For example, low latency search when designing Yelp.
- Durability: How important is it that the data in your system is not lost? For example, a social network might be able to tolerate some data loss, but a banking system cannot.
- Security: How secure does the system need to be? Consider data protection, access control, and compliance with regulations.
- Fault Tolerance: How well does the system need to handle failures? Consider redundancy, failover, and recovery mechanisms.
- Compliance: Are there legal or regulatory requirements the system needs to meet? Consider industry standards, data protection laws, and other regulations.
