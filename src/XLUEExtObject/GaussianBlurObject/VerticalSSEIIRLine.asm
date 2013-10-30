; /********************************************************************
; /* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
; /* Use of this source code is governed by a BOLT license that can be
; /* found in the LICENSE file.
; ********************************************************************/ 
; Stretch SSE main loop implement

;void Vertical_sse_iir_line(float *oTemp,  float* id, unsigned *od, int width, int height, float *a0, float *a1, float *a2, float *a3 float *b1, float *b2, float *cprev, float *cnext);
			
BITS 32

SECTION .text			
global _Vertical_sse_iir_line

_Vertical_sse_iir_line:
	push ebp
	mov ebp, esp
	sub esp, 0x10;
	push edi
	push esi
	push eax
	push ebx
	push ecx
	push edx

	%define otemp [dword ebp + 8] ; 
	%define id [dword ebp + 0x0c]
	%define od [dword ebp + 0x10]
	%define width [dword ebp + 0x14]
	%define height [dword ebp + 0x18]
	%define a0 [dword ebp+0x1c]
	%define a1 [dword ebp+0x20]
	%define a2 [dword ebp+0x24]
	%define a3 [dword ebp+0x28]
	%define b1 [dword ebp+0x2c]
	%define b2 [dword ebp+0x30]
	%define cprev [dword ebp+0x34]
	%define cnext [dword ebp+0x38]

	%define current_in [dword ebp - 0x10]

	mov eax, cprev;
	movups xmm1, [eax];
	shufps xmm1, xmm1, 0x00;

	mov esi, id;
	movups xmm2, [esi];				xmm2 : prevIn
	movups xmm4, xmm2;
	mulps xmm4, xmm1;					xmm4 : prevOut
	movups xmm6, xmm4;				xmm6 : prev2Out

	mov eax, a0;
	movups xmm1, [eax];
	shufps xmm1, xmm1, 0x00;
	mov eax, a1;
	movups xmm3, [eax];
	shufps xmm3, xmm3, 0x00;
	mov eax, b1;
	movups xmm5, [eax];
	shufps xmm5, xmm5, 0x00;
	mov eax, b2;
	movups xmm7, [eax];
	shufps xmm7, xmm7, 0x00;

	mov ecx, height;
	mov edx, otemp;

loop_top_down_start:
	movups xmm0, [esi];				xmm0 : currIn;
	mulps xmm0, xmm1;
	mulps xmm2, xmm3;
	addps xmm0, xmm2;				xmm0 : currIn * a0 + prevIn * a1;
	movups xmm2, xmm4;
	mulps xmm2, xmm5;
	mulps xmm6, xmm7;
	addps xmm2, xmm6;				xmm2 : prevOut * b1 + prev2Out * b2;
	subps xmm0, xmm2;				xmm0 : currIn * a0 + prevIn * a1 - ( prevOut * b1 + prev2Out * b2);
	movups xmm6, xmm4;				prev2Out = prevOut;
	movups xmm4, xmm0;				prevOut = result;
	movups xmm2, [esi];		prevIn = currentIn;
	movups [edx], xmm0;

	add esi, 0x10;
	add edx, 0x10;
loop_top_down_end:
	dec ecx;
	jnz loop_top_down_start;

	sub esi, 0x10;
	sub edx, 0x10;
; 开始从下往上计算
	mov eax, cnext;
	movups xmm1, [eax];
	shufps xmm1, xmm1, 0x00;
	movups xmm0, [esi]
	movups xmm2, xmm0;		
	movups xmm4, xmm2;			
	mulps xmm4, xmm1;
	movups xmm6, xmm4;

	mov eax, a2;
	movups xmm1, [eax];
	shufps xmm1, xmm1, 0x00;
	mov eax, a3;
	movups xmm3, [eax];
	shufps xmm3, xmm3, 0x00;

;od += width * (height - 1);
	mov edi, od;
	mov ecx, height;
	push ecx;
	mov eax, width;
	imul eax, 0x04;
	push eax;
	sub ecx, 1;
	imul eax, ecx;
	add edi, eax;
	pop eax;
	pop ecx;

loop_bottom_up_start:
	movups current_in, xmm0;
	mulps xmm0, xmm1;
	mulps xmm2, xmm3;
	addps xmm0, xmm2;
	movups xmm2, xmm4;
	mulps xmm2, xmm5;
	mulps xmm6, xmm7;
	addps xmm2, xmm6;
	subps xmm0, xmm2;
	movups xmm6, xmm4;
	movups xmm4, xmm0;
	movups xmm2, [edx];
	addps xmm0, xmm2;
	CVTTPS2DQ xmm0, xmm0;
	packusdw xmm0, xmm0;
	PACKUSWB xmm0, xmm0;
	pextrd ebx, xmm0, 0;
	mov [edi], ebx;

	movups xmm0, [esi];
	movups xmm2, current_in;
	
	sub esi, 0x10;
	sub edi, eax;
	sub edx, 0x10;
loop_bottom_up_end:
	dec ecx;
	jnz loop_bottom_up_start;

	pop edx
	pop ecx
	pop ebx
	pop eax
	pop esi
	pop edi

	emms
	leave 
	ret 