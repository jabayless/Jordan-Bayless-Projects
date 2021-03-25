
class squareAndSortArray{
	public int[] squareArray(int[] nums){
		for(int i = 0; i < nums.length; i++){
			nums[i] = (nums[i] * nums[i]);
		}
		return nums;
	}

	public int[] sortArray(int[] nums){
		for(int i =0; i < nums.length; i++){
			for(int j = 0; j < nums.length; j++){
				int temp = 0;
				if(nums[i] < nums[j]){
					temp = nums[i];
					nums[i] = nums[j];
					nums[j] = temp;
				}
			}
		}
		return nums;
	}

}
