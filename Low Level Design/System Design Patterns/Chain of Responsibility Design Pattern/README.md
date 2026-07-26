# Chain of Responsibility

The Chain of Responsibility pattern exists because many systems need to process a request through multiple independent steps, but hardcoding those steps together creates tightly coupled code. Imagine a request arrives, and it must be validated, authenticated, authorized, logged, rate limited, transformed, or enriched before reaching the actual business logic.

Different request types may also require different processing sequences, resulting in even more conditional logic.

The Chain of Responsibility pattern solves this by breaking the processing into small, independent handler objects, where each handler performs exactly one responsibility and then forwards the request to the next handle. Each handler only knows about its own work and the next handler, not the entire processing pipeline.