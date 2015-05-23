/*
�����Ǽ���set���ϵ�����㷨���ֱ��ǲ���set_union���set_difference������set_intersection
�ͶԳƲset_symmetric_difference�����Ǹ��������ṩ�������汾�ĺ���ԭ��
��һ���汾�ǲ���Ĭ�ϵ�����ȽϷ�ʽ operator<
�ڶ����汾���û�ͨ��comp����ָ������ʽ
ע�⣺���ĸ��㷨���ܵ��������䶼������ģ����Ҳ�������
*/

// Set algorithms: includes, set_union, set_intersection, set_difference,
// set_symmetric_difference.  All of these algorithms have the precondition
// that their input ranges are sorted and the postcondition that their output
// ranges are sorted.

// �ж�[first1, last1)�Ƿ����[first2, last2),  
// ע��: ��������Ҫ��֤����,Ĭ������ʽ��operator<����Ҫ���ж�������ʽ������õڶ��汾;
template <class _InputIter1, class _InputIter2>
bool includes(_InputIter1 __first1, _InputIter1 __last1,
              _InputIter2 __first2, _InputIter2 __last2) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  while (__first1 != __last1 && __first2 != __last2)//������������
    if (*__first2 < *__first1)//first2С��first1��ʾ������
      return false;//����FALSE
    else if(*__first1 < *__first2)//��first1С��first2 
      ++__first1;//Ѱ�ҵ�һ��������һ��λ��
    else
      ++__first1, ++__first2;//��first2����first1,�������������һλ��

  return __first2 == __last2;//���ڶ��������ȵ���β�ˣ��򷵻�TRUE
}

//�汾�����û�ͨ��comp����ָ������ʽ
template <class _InputIter1, class _InputIter2, class _Compare>
bool includes(_InputIter1 __first1, _InputIter1 __last1,
              _InputIter2 __first2, _InputIter2 __last2, _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first2, *__first1))
      return false;
    else if(__comp(*__first1, *__first2)) 
      ++__first1;
    else
      ++__first1, ++__first2;

  return __first2 == __last2;
}

//������������Ĳ�����ͬ��Ҳ�������汾
//�������[first1, last1)�������[first2, last2)�ڵ�����Ԫ��
//ע�⣺�������������������
/*
default (1)	:Ĭ����operator<����������ʽ
	template <class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result);
custom (2)	:�û�ָ��������ʽ
	template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
	OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result, Compare comp);
*/
//�汾һ��Ĭ����operator<����������ʽ
template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter set_union(_InputIter1 __first1, _InputIter1 __last1,
                      _InputIter2 __first2, _InputIter2 __last2,
                      _OutputIter __result) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  //�������䶼��δ��������β�ˣ�ִ�����²���
  while (__first1 != __last1 && __first2 != __last2) {
	  /*
	  ���������ڷֱ��ƶ������������Ƚ�Ԫ�ؽ�С��(����ΪA��)��¼��Ŀ����result
	  �ƶ�A��������ʹ��ǰ����ͬʱ��һ�����ĵ��������䡣Ȼ�����һ���µıȽϣ�
	  ��¼��Сֵ���ƶ�������...ֱ������������һ������β�ˡ������������Ԫ����ȣ�
	  Ĭ�ϼ�¼��һ�����Ԫ�ص�Ŀ����result.
	  */
    if (*__first1 < *__first2) {//first1С��first2
      *__result = *__first1;//��result��ʼֵΪfirst1
      ++__first1;//������һ���������һ��Ԫ��λ��
    }
    else if (*__first2 < *__first1) {//first2С��first1
      *__result = *__first2;//�ڶ�����Ԫ��ֵ��¼��Ŀ����
      ++__first2;//�ƶ��ڶ�����ĵ�����
    }
    else {//�������������ȵ�Ԫ�أ��ѵ�һ����Ԫ�ؼ�¼��Ŀ����
		//ͬʱ�ƶ���������ĵ�����
      *__result = *__first1;
      ++__first1;
      ++__first2;
    }
    ++__result;//����Ŀ����λ�ã��Ա�������һ�μ�¼��������
  }
  /*
  ֻҪ������֮����һ�����䵽��β�ˣ��ͽ��������whileѭ��
  ���½���δ����β�˵�����ʣ���Ԫ�ؿ�����Ŀ����
  �˿̣�[first1, last1)��[first2, last2)������һ���ǿ�����
  */
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}
//�汾�����û����ݷº���compָ���������
template <class _InputIter1, class _InputIter2, class _OutputIter,
          class _Compare>
_OutputIter set_union(_InputIter1 __first1, _InputIter1 __last1,
                      _InputIter2 __first2, _InputIter2 __last2,
                      _OutputIter __result, _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  while (__first1 != __last1 && __first2 != __last2) {
    if (__comp(*__first1, *__first2)) {
      *__result = *__first1;
      ++__first1;
    }
    else if (__comp(*__first2, *__first1)) {
      *__result = *__first2;
      ++__first2;
    }
    else {
      *__result = *__first1;
      ++__first1;
      ++__first2;
    }
    ++__result;
  }
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}
/*����:
	#include <iostream>     // std::cout
	#include <algorithm>    // std::set_union, std::sort
	#include <vector>       // std::vector

	int main () {
	  int first[] = {5,10,15,20,25};
	  int second[] = {50,40,30,20,10};
	  std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	  std::vector<int>::iterator it;

	  std::sort (first,first+5);     //  5 10 15 20 25
	  std::sort (second,second+5);   // 10 20 30 40 50

	  it=std::set_union (first, first+5, second, second+5, v.begin());
												   // 5 10 15 20 25 30 40 50  0  0
	  v.resize(it-v.begin());                      // 5 10 15 20 25 30 40 50

	  std::cout << "The union has " << (v.size()) << " elements:\n";
	  for (it=v.begin(); it!=v.end(); ++it)
		std::cout << ' ' << *it;
	  std::cout << '\n';

	  return 0;
	}
	Output:
	The union has 8 elements:
	5 10 15 20 25 30 40 50
*/

 //������������Ľ�����ͬ��Ҳ�������汾
//�������[first1, last1)�Ҵ�����[first2, last2)�ڵ�����Ԫ��
//ע�⣺���������������������������ÿ��Ԫ�ص��������͵�һ���������������ͬ
/*
default (1)	:Ĭ����operator<����������ʽ
		template <class InputIterator1, class InputIterator2, class OutputIterator>
		OutputIterator set_intersection (InputIterator1 first1, InputIterator1 last1,
                                   InputIterator2 first2, InputIterator2 last2,
                                   OutputIterator result);


custom (2)	:�û�ָ��������ʽ
		template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
		OutputIterator set_intersection (InputIterator1 first1, InputIterator1 last1,
                                   InputIterator2 first2, InputIterator2 last2,
                                   OutputIterator result, Compare comp);
*/
//�汾һ��Ĭ����operator<����������ʽ
template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter set_intersection(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _OutputIter __result) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  //���������䶼��δ����β�ˣ���ִ�����²���
  while (__first1 != __last1 && __first2 != __last2) 
	//����������ֱ��ƶ���������ֱ���������Ԫ�أ���¼��Ŀ����
	//�����ƶ�������...ֱ��������֮���е���β��
    if (*__first1 < *__first2) //��һ������Ԫ��С�ڵڶ�����Ԫ��
      ++__first1;//�ƶ���һ����ĵ���������ʱ�ڶ�����ĵ���������
    else if (*__first2 < *__first1) //�ڶ������Ԫ��С�ڵ�һ����Ԫ��
      ++__first2;//�ƶ��ڶ�����Ԫ�أ���ʱ��һ����ĵ���������
    else {//����һ����Ԫ�ص��ڵڶ�����Ԫ��
      *__result = *__first1;//����һ�������������¼��Ŀ����
	  //�ֱ��ƶ�������ĵ�����
      ++__first1;
      ++__first2;
	  //����Ŀ�������������Ա������¼Ԫ��
      ++__result;
    }
	//�������䵽��β������ֹͣwhileѭ��
	//��ʱ������Ŀ����
  return __result;
}
//�汾�����û����ݷº���compָ���������
template <class _InputIter1, class _InputIter2, class _OutputIter,
          class _Compare>
_OutputIter set_intersection(_InputIter1 __first1, _InputIter1 __last1,
                             _InputIter2 __first2, _InputIter2 __last2,
                             _OutputIter __result, _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);

  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first1, *__first2))
      ++__first1;
    else if (__comp(*__first2, *__first1))
      ++__first2;
    else {
      *__result = *__first1;
      ++__first1;
      ++__first2;
      ++__result;
    }
  return __result;
}
/*���ӣ�
	#include <iostream>     // std::cout
	#include <algorithm>    // std::set_intersection, std::sort
	#include <vector>       // std::vector

	int main () {
	  int first[] = {5,10,15,20,25};
	  int second[] = {50,40,30,20,10};
	  std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	  std::vector<int>::iterator it;

	  std::sort (first,first+5);     //  5 10 15 20 25
	  std::sort (second,second+5);   // 10 20 30 40 50

	  it=std::set_intersection (first, first+5, second, second+5, v.begin());
												   // 10 20 0  0  0  0  0  0  0  0
	  v.resize(it-v.begin());                      // 10 20

	  std::cout << "The intersection has " << (v.size()) << " elements:\n";
	  for (it=v.begin(); it!=v.end(); ++it)
		std::cout << ' ' << *it;
	  std::cout << '\n';

	  return 0;
	}
	Output:
	The intersection has 2 elements:
	10 20
*/

 //������������Ĳ��ͬ��Ҳ�������汾
//�������[first1, last1)����������[first2, last2)�ڵ�����Ԫ��
//ע�⣺���������������������������ÿ��Ԫ�ص��������͵�һ���������������ͬ
/*
default (1)	:Ĭ����operator<����������ʽ
		template <class InputIterator1, class InputIterator2, class OutputIterator>
		OutputIterator set_difference (InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 OutputIterator result);



custom (2)	:�û�ָ��������ʽ
		template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
		OutputIterator set_difference (InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 OutputIterator result, Compare comp);
*/
//�汾һ��Ĭ����operator<����������ʽ
template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter set_difference(_InputIter1 __first1, _InputIter1 __last1,
                           _InputIter2 __first2, _InputIter2 __last2,
                           _OutputIter __result) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  //���������䶼��δ����β�ˣ���ִ�����²���
  while (__first1 != __last1 && __first2 != __last2)
	 /*
	 ����������ֱ��ƶ�������������һ����Ԫ�ص��ڵڶ�����Ԫ��ʱ����ʾ�����乲ͬ���ڸ�Ԫ��
	 ��ͬʱ�ƶ���������
	 ����һ����Ԫ�ش��ڵڶ�����Ԫ��ʱ�����õڶ����������ǰ����
	 ��һ����Ԫ��С�ڵڶ�����Ԫ��ʱ���ѵ�һ����Ԫ�ؼ�¼��Ŀ����
	�����ƶ�������...ֱ��������֮���е���β��
	*/
    if (*__first1 < *__first2) {//��һ����Ԫ��С�ڵڶ�����Ԫ��
      *__result = *__first1;//�ѵ�һ����Ԫ�ؼ�¼��Ŀ����
      ++__first1;//�ƶ���һ���������
      ++__result;//����Ŀ�������Ա������¼����
    }
    else if (*__first2 < *__first1)//����һ�����Ԫ�ش��ڵڶ������Ԫ��
      ++__first2;//�ƶ��ڶ����������,ע�⣺���ﲻ��¼�κ�Ԫ��
    else {//���������Ԫ�����ʱ,ͬʱ�ƶ�������ĵ�����
      ++__first1;
      ++__first2;
    }
	//���ڶ������ȵ���β�ˣ���ѵ�һ����ʣ���Ԫ�ظ��Ƶ�Ŀ����
  return copy(__first1, __last1, __result);
}
//�汾�����û����ݷº���compָ���������
template <class _InputIter1, class _InputIter2, class _OutputIter, 
          class _Compare>
_OutputIter set_difference(_InputIter1 __first1, _InputIter1 __last1,
                           _InputIter2 __first2, _InputIter2 __last2, 
                           _OutputIter __result, _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);

  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first1, *__first2)) {
      *__result = *__first1;
      ++__first1;
      ++__result;
    }
    else if (__comp(*__first2, *__first1))
      ++__first2;
    else {
      ++__first1;
      ++__first2;
    }
  return copy(__first1, __last1, __result);
}
/*���ӣ�
	#include <iostream>     // std::cout
	#include <algorithm>    // std::set_difference, std::sort
	#include <vector>       // std::vector

	int main () {
	  int first[] = {5,10,15,20,25};
	  int second[] = {50,40,30,20,10};
	  std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	  std::vector<int>::iterator it;

	  std::sort (first,first+5);     //  5 10 15 20 25
	  std::sort (second,second+5);   // 10 20 30 40 50

	  it=std::set_difference (first, first+5, second, second+5, v.begin());
												   //  5 15 25  0  0  0  0  0  0  0
	  v.resize(it-v.begin());                      //  5 15 25

	  std::cout << "The difference has " << (v.size()) << " elements:\n";
	  for (it=v.begin(); it!=v.end(); ++it)
		std::cout << ' ' << *it;
	  std::cout << '\n';

	  return 0;
	}
	Output��
	The difference has 3 elements:
	5 15 25
*/

 //������������ĶԳƲ��ͬ��Ҳ�������汾
//�������[first1, last1)����������[first2, last2)�ڵ�����Ԫ���Լ�������[first2, last2)����������[first1, last1)
//ע�⣺�������������������
/*
default (1)	:Ĭ����operator<����������ʽ
		template <class InputIterator1, class InputIterator2, class OutputIterator>
		OutputIterator set_symmetric_difference (InputIterator1 first1, InputIterator1 last1,
                                           InputIterator2 first2, InputIterator2 last2,
                                           OutputIterator result);


custom (2)	:�û�ָ��������ʽ
		template <class InputIterator1, class InputIterator2,
          class OutputIterator, class Compare>
		OutputIterator set_symmetric_difference (InputIterator1 first1, InputIterator1 last1,
                                           InputIterator2 first2, InputIterator2 last2,
                                           OutputIterator result, Compare comp);
*/
//�汾һ��Ĭ����operator<����������ʽ
template <class _InputIter1, class _InputIter2, class _OutputIter>
_OutputIter 
set_symmetric_difference(_InputIter1 __first1, _InputIter1 __last1,
                         _InputIter2 __first2, _InputIter2 __last2,
                         _OutputIter __result) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_REQUIRES(typename iterator_traits<_InputIter1>::value_type,
                 _LessThanComparable);
  //���������䶼��δ����β�ˣ���ִ������Ĳ���
  while (__first1 != __last1 && __first2 != __last2)
	  /*
	  ���1����������Ԫ����ȣ���ͬʱ�ƶ�������ĵ�����.
	  ���2������һ�����Ԫ��С�ڵڶ�����Ԫ�أ���ѵ�һ����Ԫ�ؼ�¼��Ŀ���������ƶ���һ���������.
	  ���3������һ�����Ԫ�ش��ڵڶ�����Ԫ�أ���ѵڶ�����Ԫ�ؼ�¼��Ŀ���������ƶ��ڶ����������.
	  */
    if (*__first1 < *__first2) {//�������2
      *__result = *__first1;//�ѵ�һ����Ԫ�ؼ�¼��Ŀ����
      ++__first1;//�ƶ���һ���������.��ʱ�ڶ��������������
      ++__result;
    }
    else if (*__first2 < *__first1) {//�������3
      *__result = *__first2;//�ѵڶ�����Ԫ�ؼ�¼��Ŀ����
      ++__first2;//�ƶ��ڶ����������.��ʱ��һ�������������
      ++__result;
    }
    else {//�������1
		//ͬʱ�ƶ�������ĵ�����
      ++__first1;
      ++__first2;
    }
	 /*
  ֻҪ������֮����һ�����䵽��β�ˣ��ͽ��������whileѭ��
  ���½���δ����β�˵�����ʣ���Ԫ�ؿ�����Ŀ����
  �˿̣�[first1, last1)��[first2, last2)������һ���ǿ�����
  */
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}

//�汾�����û����ݷº���compָ���������
template <class _InputIter1, class _InputIter2, class _OutputIter,
          class _Compare>
_OutputIter 
set_symmetric_difference(_InputIter1 __first1, _InputIter1 __last1,
                         _InputIter2 __first2, _InputIter2 __last2,
                         _OutputIter __result,
                         _Compare __comp) {
  __STL_REQUIRES(_InputIter1, _InputIterator);
  __STL_REQUIRES(_InputIter2, _InputIterator);
  __STL_REQUIRES(_OutputIter, _OutputIterator);
  __STL_REQUIRES_SAME_TYPE(
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  __STL_BINARY_FUNCTION_CHECK(_Compare, bool,
       typename iterator_traits<_InputIter1>::value_type,
       typename iterator_traits<_InputIter2>::value_type);
  while (__first1 != __last1 && __first2 != __last2)
    if (__comp(*__first1, *__first2)) {
      *__result = *__first1;
      ++__first1;
      ++__result;
    }
    else if (__comp(*__first2, *__first1)) {
      *__result = *__first2;
      ++__first2;
      ++__result;
    }
    else {
      ++__first1;
      ++__first2;
    }
  return copy(__first2, __last2, copy(__first1, __last1, __result));
}
/*���ӣ�
	#include <iostream>     // std::cout
	#include <algorithm>    // std::set_symmetric_difference, std::sort
	#include <vector>       // std::vector

	int main () {
	  int first[] = {5,10,15,20,25};
	  int second[] = {50,40,30,20,10};
	  std::vector<int> v(10);                      // 0  0  0  0  0  0  0  0  0  0
	  std::vector<int>::iterator it;

	  std::sort (first,first+5);     //  5 10 15 20 25
	  std::sort (second,second+5);   // 10 20 30 40 50

	  it=std::set_symmetric_difference (first, first+5, second, second+5, v.begin());
												   //  5 15 25 30 40 50  0  0  0  0
	  v.resize(it-v.begin());                      //  5 15 25 30 40 50

	  std::cout << "The symmetric difference has " << (v.size()) << " elements:\n";
	  for (it=v.begin(); it!=v.end(); ++it)
		std::cout << ' ' << *it;
	  std::cout << '\n';

	  return 0;
	}
	Output��
	The symmetric difference has 6 elements:
	5 15 25 30 40 50
*/