## Architecture

This architecture will be based on a request-response cycle. A request is a "question" or any statement that we ask to Chanakya and the response is an answer.

The knowledge base must be totally configurable. And I don't mean the topic of the knowledge base. The base itself can be changed, ie, it doesnt have to conform to a tree structure.

There must be also be support for "plugins", in this case implemented as middleware that can be added to a configuration file or something.

The configuration file can be written in C++, we don't need any of that non-native shit.

Chanakya needs to be written very functional as we might need to create wrappers on top of this:- such as shell scripts, maybe API packages and so on. It could be like an SQL database where it runs in the server in localhost and maybe we can connect to it.

It should probably run as a daemon.

Making it functional might help in making it more concurrent, I don't know.

There might be a need for Chanakya to not just be a conversational chatbot. Maybe we want responses from Chanakya which are not triggered by the user, but by the environment.

We might need a layer on top of the following workflow so that we can manage multiple requests coming in simultaneously.

## Request-Response Workflow

1. A `Request` is sent to a request processing queue.
	* The `Request` object consists of a `Metadata` object and a `Context` object.
		* The `Metadata` object consists of information about the `Request` object, ie, type of request and some additional data that comes with it.
		* The `Context` object is just a key-value store that can contain any kind of information.
2. When the `Request` object reaches the front of the queue, it is sent for processing.
3. When this happens, the `Request` object is first sent through all the middleware present.
	* Each middleware has access to the `Request` object, control flow and the `Response` object.
	* The middleware can control whether the `Request` actually goes to the next function in order.
	* The middleware is basically a function.
4. The `Request` reaches the request processor.
	* The request processor has access to a knowledge base.
	* The logic for the request processor and the knowledge base can be customised.
5. The request processor generates a `Response` object and returns it.
6. The `Response` is sent through all the middleware again, but this time in reverse order.
7. It is the finally sent back to the client.
