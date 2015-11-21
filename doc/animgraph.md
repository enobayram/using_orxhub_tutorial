Animation Graph Config Mini-DSL
===============================

This package introduces a mini-language for defining `AnimationSet` sections. Normally, this is how you would define an animation set:  

Introduction By Example
-----------------------

```ini
[SoldierWalk]
KeyData...

[SoldierRun]
KeyData...

[SoldierWalkToRun]
Source      = SoldierWalk
Destination = SoldierRun
Immediate   = true

... ; More animToanim sections
 
[SoldierAnimSet]
AnimationList = SoldierWalk # SoldierRun # ... ; more anims
LinkList      = SoldierWalkToWalk # SoldierWalkToRun # ... ; more links
```

This package introduces a mini-DSL to shorten the above code into:

```ini
; Animation sections are defined as before
[SoldierWalk]
KeyData...

[SoldierRun]
KeyData...

; No need to define the link sections

[SoldierAnimSet]
;No AnimationList or LinkList field needed, they're derived from AnimationGraph
Walk = SoldierWalk
Run  = SoldierRun
AnimationGraph = Walk,Run!:Walk,!Run
%ConfigX.ProcessAnimGraph SoldierAnimSet ; Transformation happens here
```

This transformation greatly reduces the amount of code needed, but it also introduces a level of indirection. Now the code that sets the object's the animations can use the generic tags "Walk" and "Run" instead of "SoldierWalk" and "SoldierRun", so that the same code can work on multiple objects with different walk and run animations.

DSL Specification
-----------------
The heart of this package is the animation graph specification in the `AnimationGraph` field of the `AnimationSet` section. The DSL is specified as:  

```
AnimationGraph = Term # Term # Term ...

Term = Subterm : Subterm : Subterm ...

Subterm = Item , Item , Item ...

Item = [!] TagName [!]
```

Each _Term_ indicates a set of animation links. If the _Term_ is simply an animation tag, a loop link section is created. Otherwise if it's a `:` separated list of _Subterms_, then a collection of link sections between the tags in the `Subterms` is created.

Whenever a _Subterm_ is to the left of `:` it becomes the _Source_ of an animation link, and whenever it's to the right or `:` it becomes the _Destination_. If it's between two `:`'s then it becomes the _Source_ and the _Destination_ of two separate link sections. 

The _Subterms_ can themselves contain multiple `,` separated items. If a _Subterm_ couple (separated by `:`) contains _N_ _Items_ on the left and _M_ _Items_ on the right, then _N x M_   link sections are generated as the cartesian product of the list on the left and the right.

An _Item_ consists of a specific animation tag (like "Run" or "Walk") optionally prefixed and/or suffixed with a `!`. The presence of a `!` prefix indicates that all incoming links will have the `Immediate=true` property. A `!` suffix indicates the same for outgoing links.

Registered Commands
-------------------
**ConfigX.ProcessAnimGraph -SectionName-**: The DSL described above is parsed and applied to the config section by this

**ObjectX.SetAnimByTag -Object- -Tag- [Current=false]**: Set the current/target(Indicated by _Current_) animation for _Object_ using an animation tag.

**bool ObjectX.AnimHasTag -Object- -Tag- [Current=false]**: Returns whether the current/target animation has the given _Tag_.
