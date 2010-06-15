/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
#ifndef _KSTAND_H_
#define _KSTAND_H_
#define KI_VERSION_ALPHA 1
#define KI_VERSION_BETA 2
#define KI_VERSION_RC 3
#define KI_VERSION_STABLE 4

#define KI_VERSION_MAJOR 0
#define KI_VERSION_MINOR 1
#define KI_VERSION_REVISION 0
#define KI_VERSION_BUILD KI_VERSION_ALPHA

#ifdef _KSTAND_INC_KI_INFO_H_

#ifndef KI_NOTOFFICIAL_BUILD
const char ki_about_message[] = "\
Advanced Simulated Directory Flora (ASDF) 0.1.0.1\r\n\
Copyright 2010 by Robert Christian Taylor (r0wbrt)\r\n\r\n\
THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND\r\n\
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\r\n\
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\r\n\
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\r\n\
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\r\n\
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\r\n\
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\r\n\
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\r\n\
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\r\n\
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\r\n\
SUCH DAMAGE.\r\n\r\n\
Email Bug Reports or Feature Requests to: r0wbrt@gmail.com\r\n\r\n";
#else
const char ki_about_message[] = "\
Advanced Simulated Directory Flora (ASDF) 0.1.0.1\r\n\
Copyright 2010 by Robert Christian Taylor (r0wbrt)\r\n\
Copyright Modifications by Distributor\r\n\r\n\
THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND\r\n\
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\r\n\
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE\r\n\
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE\r\n\
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\r\n\
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\r\n\
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\r\n\
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT\r\n\
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY\r\n\
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF\r\n\
SUCH DAMAGE.\r\n\r\n\
For Bug Reports and Feature Requests Contact your Distributor\r\n\r\n";
#endif


const char ki_version[] = "0.1.0.1";

#ifndef KI_NOTOFFICIAL_BUILD
const char ki_maintainer[] = "Robert Christian Taylor r0wbrt@gmail.com";
#else
const char ki_maintainer[] = "Custom Built, Contact your Distributor";
#endif


#if KI_VERSION_BUILD != KI_VERSION_STABLE
const char ki_name[] = "Unstable";
#else
const char ki_name[] = "Stable";
#endif

#ifndef KI_NOTOFFICIAL_BUILD
const char ki_copyright[] = "Copyright 2010 by Robert Christian Taylor (r0wbrt)";
#else
const char ki_copyright[] = "Copyright 2010 by Robert Christian Taylor (r0wbrt) and Copyright Modifications by Distributor";
#endif

#endif
#endif
