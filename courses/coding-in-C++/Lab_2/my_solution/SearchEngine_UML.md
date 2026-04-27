# Search Engine System - UML Diagrams

## Class Diagram

```mermaid
classDiagram
    class WebResource {
        - String url
        - String content
        - int ranking
        - bool /isPopular
        + displayState() void {query}
        + getRanking() int {query}
        + getUrl() String {query}
        + getContent() String {query}
    }

    class Query {
        - String text
        - int maxResults
        + isValid() bool {query}
        + getText() String {query}
        + getMaxResults() int {query}
    }

    class SearchEngine {
        - static int totalQueriesExecuted
        + processQuery(in q: Query) void
        + getBasicInfo() String {query}
        + addResource(in w: WebResource) void
    }
```

## Object Diagram

```mermaid
classDiagram
    %% Object Diagram for the Search Engine System
    
    object "<u>google : SearchEngine</u>" as se {
        totalQueriesExecuted = 42
    }
    
    object "<u>cppDocs : WebResource</u>" as wr1 {
        url = "https://en.cppreference.com"
        content = "C++ documentation and reference..."
        ranking = 95
        isPopular = true
    }
    
    object "<u>myBlog : WebResource</u>" as wr2 {
        url = "https://myblog.url/cpp"
        content = "My first C++ program!"
        ranking = 12
        isPopular = false
    }

    object "<u>searchCpp : Query</u>" as q1 {
        text = "C++ pointers"
        maxResults = 10
    }
```
