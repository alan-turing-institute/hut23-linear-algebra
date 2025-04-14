// public domain software, by Theodore H. Smith
// compile with:
// clang -framework OpenCL opencl.cpp; ./a.out

#include <stdio.h>
#include <OpenCL/opencl.h>

char kernel_code[] = 
  "kernel void square_root (global float* in, global float* out) { \n\
     int id = get_global_id(0); \n\
     out[id] = sqrt(in[id]); \n\
   }";

int main() {
	cl_device_id gpu;
	cl_int result;
	float in[3] = {9, 25, 64};
	float out[3] = {-1, -2, -3};
    
	clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &gpu, NULL);
	cl_context context = clCreateContext(NULL, 1, &gpu, NULL, NULL, &result);
	
	if (result != CL_SUCCESS)
		return puts("Couldn't create context")-1;
	
	cl_command_queue queue = clCreateCommandQueue(context, gpu, 0, &result);
	
	if (result != CL_SUCCESS)
		return puts("Couldn't create command queue")-1;
	
	cl_program program = clCreateProgramWithSource(context, 1, (const char*[]){kernel_code}, NULL, &result);
	if (result != CL_SUCCESS)
		return puts("Can't create program")-1;
	
	result = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (result != CL_SUCCESS)
		return puts("Can't build program")-1;
	
	cl_mem buffer_in = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float)*3, NULL, &result);
	if (result != CL_SUCCESS)
		return puts("Can't initialise input buffer")-1;

	cl_mem buffer_out = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float)*3, NULL, &result);
	if (result != CL_SUCCESS)
		return puts("Can't initialise output buffer")-1;

	result = clEnqueueWriteBuffer(queue, buffer_in, CL_TRUE, 0, sizeof(float)*3, in, 0, NULL, NULL);
	if (result != CL_SUCCESS)
		return puts("Can't enqueue write buffer")-1;
	
	cl_kernel kernel = clCreateKernel(program, "square_root", NULL);
	clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer_in);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), &buffer_out);
	
	size_t count = 3;
	clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &count, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(queue, buffer_out, CL_TRUE, 0, sizeof(float)*3, out, 0, NULL, NULL);
	clFinish(queue);
	
	for (int i = 0; i < 3; i++)
		printf("%f\n", out[i]);

	return puts("OK");
}
