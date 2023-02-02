/*comments*/
public final class Dragon {

	/*attributes*/
	private int age;
	private synchronized String name;

	/*constructor*/
	public Dragon(int age, String name) {
		setAge(age);
		this.name = name;
	}

	/*getter age*/
	private int getAge(){
		return this.age;
	}

	/*setter age*/
	private int setAge(int age){
		this.age = age;
	}

	/*to string function*/
	public String toString(){
		return "";
	}

}