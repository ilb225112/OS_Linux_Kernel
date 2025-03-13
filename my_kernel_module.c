#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/mm.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PES1UG23CS167");
MODULE_DESCRIPTION("Process Tree Viewer with Memory Map");
MODULE_VERSION("1.0");

void print_memory_map(struct mm_struct *mm, int depth);
void print_process_tree(struct task_struct *task, int depth);


static int parent_pid = 1;
module_param(parent_pid, int, 0444);
MODULE_PARM_DESC(parent_pid, "Parent process ID to display process tree");

// Function to print memory regions
void print_memory_map(struct mm_struct *mm, int depth) {
    struct vm_area_struct *vma = NULL;

    if (!mm) return;  // Skip if no memory info

    pr_info("%*s[Memory Map]\n", depth * 4, "");

    unsigned long addr = mm->mmap_base;
    while ((vma = find_vma(mm, addr))) {
        pr_info("%*s   Region: Start=0x%lx, End=0x%lx, Size=%lu KB\n",
                (depth + 1) * 4, "", vma->vm_start, vma->vm_end, 
                (vma->vm_end - vma->vm_start) / 1024);
        addr = vma->vm_end + 1;  // Move to next VMA
    }
}

// Function to recursively print process tree
void print_process_tree(struct task_struct *task, int depth) {
    unsigned long heap_size = 0, stack_size = 0;

    if (task->mm) {
        heap_size = (task->mm->brk - task->mm->start_brk) / 1024;
        stack_size = (task->mm->start_stack - task->mm->stack_vm) / 1024;
    }

    if (depth == 0) {
    pr_info("%*s|-- 👴 Process: %s [PID: %d] [PPID: %d] (Heap: %lu KB, Stack: %lu KB)\n",
            depth * 4, "", task->comm, task->pid, task->real_parent->pid, heap_size, stack_size);
} else if (depth == 1) {
    pr_info("%*s|-- 🧑 Process: %s [PID: %d] [PPID: %d] (Heap: %lu KB, Stack: %lu KB)\n",
            depth * 4, "", task->comm, task->pid, task->real_parent->pid, heap_size, stack_size);
} else {
    pr_info("%*s|-- 👶 Process: %s [PID: %d] [PPID: %d] (Heap: %lu KB, Stack: %lu KB)\n",
            depth * 4, "", task->comm, task->pid, task->real_parent->pid, heap_size, stack_size);
}


    // Print memory map
    print_memory_map(task->mm, depth);

    // Recursively print child processes
    struct task_struct *child;
    struct list_head *list;
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        print_process_tree(child, depth + 1);
    }
}

// Module initialization function
static int __init my_module_init(void) {
    struct task_struct *task;
    pr_info("Kernel Module Loaded: Process Tree Viewer\n");

    for_each_process(task) {
        if (task->pid == parent_pid) {
            pr_info("Displaying process tree for 👴 Parent ->PID %d\n", parent_pid);
            print_process_tree(task, 0);
            break;
        }
    }

    return 0;
}

// Module exit function
static void __exit my_module_exit(void) {
    pr_info("Kernel Module Unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

