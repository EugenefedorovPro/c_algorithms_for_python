import factory

unsorted_list = [3, 2, 1]
sorting_alg = "merge_inplace"
result = factory.factory(sorting_alg, unsorted_list)
print(f"result of sorting '{unsorted_list}' with '{sorting_alg}' alg = {result}")
