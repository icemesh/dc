# dc
In this repository you're gonna find a format specification for the script files used in the Naughty Dog Engine.
This is still a work in progress. 

# What's DC
DC is a runtime scripting language thats integrated into the Naughty Dog engine since Uncharted Drake's Fortune (you can find a presentation by Dan Liebgold [here](https://gdcvault.com/play/211/Adventures-in-Data-Compilation-and))
Its format changed in Uncharted 2 Among Thieves with the introduction of State Scripts. 
A state script is compromised of:
* attributes
* states

States define object's behavior via runtime script code:

* response to events
* natural behavior over time
* transition between states

An example of a state script is as follows:
```
(define-state-script ss-example
	:initial-state 'initial  	;;state from where start executing. you can see this as a main/entry point
	:options (new ss-options :wait-for-levels (make-symbol-array 'player))
	:declarations (declaration-list
			(var 'upgrade-level	:type int32 :default 0) ;;define a int32 variable with value 0;
			(var 'attacker-id	:type symbol)           ;;define a variable of type symbol (aka StringId)
	)
	
	(state ('initial)
		(on (start)
			(go 'next-state)
		)
	)
	
	(state ('next-state)
		(on (start)
			;;Do something at the start of the frame that the script enters this state
			(set-int32 'upgrade-level (+ (get-int32 upgrade-level) 1)) ;;increment the value of upgrade-level of 1
			(wait 4.0) ;;wait 4 seconds
			(go 'done) ;;go to the next state
		)
		(on (update)
			;;call some code on the update of every frame
		)
	)
	
	(state ('done)
		(on (start)
			(print-string "bye bye")
		)
	)
)
```
