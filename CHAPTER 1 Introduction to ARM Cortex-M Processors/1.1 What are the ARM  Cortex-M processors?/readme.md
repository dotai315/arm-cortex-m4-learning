<h3>1.1.1 The Cortex-M3 and Cortex-M4 processors</h3> 
<p>32-bit architecture. The Instruction Set Architecture (ISA) is called the Thumb ISA and is based on Thumb-2 Technology which supports a mixture of 16-bit and 32-bit instructions.</p>
<p>The Cortex-M3 and Cortex-M4 processors have:</p>
<ul>
  <li>Three-stage pipeline design</li>
  <li>Harvard bus architecture</li>
  <li>32-bit addressing, supporting 4GB of memory space</li>
  <li>On-chip bus interfaces based on ARM AMBA</li>
  <li>NVIC (Nested Vectored Interrupt Controller) up to 240 interrupt requests and from 8 to 256 interrupt priority levels</li>
  <li>Support for various features for OS: SysTick timer, shadowed stack pointer</li>
  <li>Low power features</li>
  <li>MPU (Memory Protection Unit) </li>
  <li>Bit-data accesses in two specific memory regions using Bit Band</li>
  <li>Single processor or multi-processor designs</li>
</ul>
<p>The ISA used in Cortex-M3 and Cortex-M4 processors provides a wide range of instructions:</p>
<ul>
  <li>General data processing</li>
  <li>Memory access instructions supporting 8-bit, 16-bit, 32-bit, and 64-bit data</li>
  <li>Instructions for bit field processing</li>
  <li>Multiply Accumulate (MAC) and saturate instructions</li>
  <li>iInstructions for branches, conditional branches and function calls</li>
  <li>Instructions for system control, OS support, etc.</li>
</ul>
<p>In addition, the Cortex-M4 processor also supports:</p>
<ul>
  <li>Single Instruction Multiple Data (SIMD) operations</li>
  <li>Additional fast MAC and multiply instructions</li>
  <li>Saturating arithmetic instructions</li>
  <li>Optional floating point instructions</li>
</ul>
<h3>1.1.2 The Cortex-M processor family</h3>
<img src="https://user-images.githubusercontent.com/57071897/152416457-e3fa6b5e-4fc6-4a7c-98fa-746cd6d7998d.png"></img>
<p> 
  Cortex-M0, Cortex-M0+, and the Cortex-M1 processors are based on ARMv6-M, which has a smaller instruction set. The Cortex-M0+ processor has the most state-of-the-art low power optimizations, and has more available optional features.
</p>
<p>
  The Cortex-M3 and Cortex-M4 processors are based on ARMv7-M architec-
ture. Both are high-performance processors that are designed for microcontrollers.
Because the Cortex-M4 processor has SIMD, fast MAC, and saturate arithmetic in-
structions, it can also carry out some of the digital signal processing applications
that traditionally have been carried out by a separate Digital Signal Processor
(DSP).
</p>
<p>
  The Cortex-M1 processor is designed specifically for FPGA applications. It has
Tightly Coupled Memory (TCM) features.
</p>
