class Solution {
    public void merge(int[] nums1, int m, int[] nums2, int n) {
        int[] mergedArray = new int[n+m];
        int i =0, j = 0, k = 0;
        
        while(k < (nums1.length)){
            
            if(nums2.length == 0){
                mergedArray = nums1;
                break;
            }
            
            if(nums1.length == 0){
                mergedArray = nums2;
                break;
            }
            
            if((nums1[i] <= nums2[j]) && (i < m)){
                mergedArray[k] = nums1[i];
                i++;
            }
            
            else {
                mergedArray[k] = nums2[j];
                    j++;
            }
            
            k++;
            if(j == n){
                    while(i < m){
                        mergedArray[k] = nums1[i];
                        i++; k++;
                    }
                }
        }
        
        for(int l = 0; l < (n+m); l++){
            nums1[l] = mergedArray[l];
        }
    }
}
