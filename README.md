
# animation-lib
A simple c++ library that wraps up the [Windows Animation Manager](https://learn.microsoft.com/en-us/windows/win32/api/_uianimation/) in a easy to use package. 

The current version, only covers a fraction if the functionality of Windows Animation Manager, but can still be use to make very simple animations.

### Building the Project

#### Debug

Follow these steps to build the project (with the test app):

1. **Create a build directory & configure the build:**
   ```bash
   cmake -S. -Bbuild -DBUILD_TESTS=ON
   ```

2. **Build the project:**
   ```bash
   cmake --build build -j
   ```

#### Release

For release build use `--config Release`:

```bash
cmake -S. -Bbuild -DBUILD_TESTS=ON
cmake --build build -j --config Release
```

### Usage
animation-lib is pretty simple to use, just follow these steps.

#### Step 1
Create and store a `TransitionLibrary` and an `Animation`
```cpp
{
	...

	HRESULT hr = CoInitializeEx(...);
	m_TransitionLibrary = std::make_unique<anim::TransitionLibrary>();
	m_Animation = std::make_unique<anim::Animation>();

	...
}
```

#### Step 2
Create a `AnimationTimerEventHandler` class and give an instance of it to the `Animation` object
```cpp
class MyTimerEventHandler : public anim::AnimationTimerEventHandler
{
public:
	void OnPostUpdate() override
	{
		// Handle the timer event here
		// For example, redraw the window containing an animation
	}
};

{
	...

	// Insantiate the timer event handler and set it on the animation object.
	auto timerEventHandler = new MyTimerEventHandler>();
	m_Animation->SetTimerEventHandler(timerEventHandler);

	...
}
```

#### Step 3
Create an `AnimationVariable` and (optionlly) implement a `VariableChangeHandler` class
```cpp
class MyVariableChangeHandler : public anim::VariableChangeHandler
{
public:
	void OnVariableChanged(
		IUIAnimationStoryboard* storyboard,
		IUIAnimationVariable* variable,
		double newValue,
		double previousValue) override
	{
		// Handle the variable change here, e.g savee the new value for later use
		m_MyVariable = newValue;
	}
};

{
	...

	// Create the variable
	m_AnimationVariable = m_Animation->CreateVariable(10.0);

	// Optionally, create a change handler to handle variable changes
	m_ChangeHandler = new MyVariableChangeHandler();
	m_ChangeHandler->AddRef(); // Ensure the handler is kept alive if you plan on storing it
	m_AnimationVariable.lock()->SetChangeHandler(m_ChangeHandler);

	...
}
```

##### Step 4
Create a `Storyboard`, a transition for your variable and start the storyboard
```cpp
{
	...

	//Create a storyboard to hold the transitions
	auto storyboard = m_Animation->CreateStoryboard();

	// Create a linear transtion that will run for 2 seconds and transition the variable to 100.
	// NOTE: The transition library returns shared pointers, so store the transition so it is not deleted.
	m_Transition = m_TransitionLibrary.CreateLinearTransition(2, 100);

	// Add the transition and variable to the storyboard
	storyboard->AddTransition(m_Transition, *m_AnimationVariable);

	// Schedule the storyboard
	storyboard->Schedule( m_Animation->GetTime() );

	...
}
```

##### Step 5
Do something with the animation variable, like use it as one of the coordinates of a rectangle. 
The possibilities are endless!


### License

MIT License. Can be used in closed-source commercial products.

