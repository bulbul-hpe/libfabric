/* SPDX-License-Identifier: BSD-2-Clause OR GPL-2.0-only */
/* SPDX-FileCopyrightText: Copyright Amazon.com, Inc. or its affiliates. All rights reserved. */

#ifndef EFA_UNIT_TEST_RDMA_CORE_MOCKS_H
#define EFA_UNIT_TEST_RDMA_CORE_MOCKS_H

extern struct efa_unit_test_mocks g_efa_unit_test_mocks;

struct efa_mock_ibv_send_wr_list
{
	struct ibv_send_wr *head;
	struct ibv_send_wr *tail;
};

void efa_mock_ibv_send_wr_list_destruct(struct efa_mock_ibv_send_wr_list *wr_list);

struct ibv_ah *__real_ibv_create_ah(struct ibv_pd *pd, struct ibv_ah_attr *attr);

struct ibv_ah *efa_mock_ibv_create_ah_check_mock(struct ibv_pd *pd, struct ibv_ah_attr *attr);

int __real_efadv_query_device(struct ibv_context *ibvctx, struct efadv_device_attr *attr,
			      uint32_t inlen);

int efa_mock_efadv_query_device_return_mock(struct ibv_context *ibvctx, struct efadv_device_attr *attr,
					    uint32_t inlen);

extern void *g_ibv_submitted_wr_id_vec[EFA_RDM_EP_MAX_WR_PER_IBV_POST_SEND];

extern int g_ibv_submitted_wr_id_cnt;

void efa_ibv_submitted_wr_id_vec_clear();

void efa_mock_ibv_wr_start_no_op(struct ibv_qp_ex *qp);

void efa_mock_ibv_wr_send_save_wr(struct ibv_qp_ex *qp);

void efa_mock_ibv_wr_send_verify_handshake_pkt_local_host_id_and_save_wr(struct ibv_qp_ex *qp);

void efa_mock_ibv_wr_rdma_write_save_wr(struct ibv_qp_ex *qp, uint32_t rkey,
					uint64_t remote_addr);

void efa_mock_ibv_wr_set_inline_data_list_no_op(struct ibv_qp_ex *qp,
						size_t num_buf,
						const struct ibv_data_buf *buf_list);

void efa_mock_ibv_wr_set_sge_list_no_op(struct ibv_qp_ex *qp,
					size_t num_sge,
					const struct ibv_sge *sge_list);

void efa_mock_ibv_wr_set_ud_addr_no_op(struct ibv_qp_ex *qp, struct ibv_ah *ah,
				       uint32_t remote_qpn, uint32_t remote_qkey);

int efa_mock_ibv_wr_complete_no_op(struct ibv_qp_ex *qp);

int efa_mock_ibv_start_poll_return_mock(struct ibv_cq_ex *ibvcqx,
					struct ibv_poll_cq_attr *attr);

int efa_mock_ibv_start_poll_use_saved_send_wr_with_mock_status(struct ibv_cq_ex *ibvcqx,
							       struct ibv_poll_cq_attr *attr);

int efa_mock_ibv_next_poll_return_mock(struct ibv_cq_ex *ibvcqx);

int efa_mock_ibv_next_poll_use_saved_send_wr_with_mock_status(struct ibv_cq_ex *ibvcqx);

void efa_mock_ibv_end_poll_check_mock(struct ibv_cq_ex *ibvcqx);

uint32_t efa_mock_ibv_read_opcode_return_mock(struct ibv_cq_ex *current);

uint32_t efa_mock_ibv_read_vendor_err_return_mock(struct ibv_cq_ex *current);

uint32_t efa_mock_ibv_read_qp_num_return_mock(struct ibv_cq_ex *current);

uint32_t efa_mock_ibv_read_wc_flags_return_mock(struct ibv_cq_ex *current);

uint32_t efa_mock_ibv_wc_read_imm_data_return_mock(struct ibv_cq_ex *current);

bool efa_mock_efadv_wc_is_unsolicited(struct efadv_cq *efadv_cq);

void efa_mock_ibv_wr_send_imm_save_wr(struct ibv_qp_ex *qp, __be32 imm_data);

ssize_t __real_ofi_copy_from_hmem_iov(void *dest, size_t size,
				      enum fi_hmem_iface hmem_iface, uint64_t device,
				      const struct iovec *hmem_iov,
				      size_t hmem_iov_count, uint64_t hmem_iov_offset);

extern int g_ofi_copy_from_hmem_iov_call_counter;
ssize_t efa_mock_ofi_copy_from_hmem_iov_inc_counter(void *dest, size_t size,
						    enum fi_hmem_iface hmem_iface, uint64_t device,
						    const struct iovec *hmem_iov,
						    size_t hmem_iov_count, uint64_t hmem_iov_offset);

int __real_efa_rdm_pke_read(struct efa_rdm_ope *ope);

bool __real_efa_device_support_unsolicited_write_recv();

int efa_mock_efa_rdm_pke_read_return_mock(struct efa_rdm_ope *ope);

ssize_t __real_efa_rdm_pke_proc_matched_rtm(struct efa_rdm_pke *pkt_entry);

ssize_t efa_mock_efa_rdm_pke_proc_matched_rtm_no_op(struct efa_rdm_pke *pkt_entry);

ssize_t __real_efa_rdm_ope_post_send(struct efa_rdm_ope *ope, int pkt_type);

ssize_t efa_mock_efa_rdm_ope_post_send_return_mock(struct efa_rdm_ope *ope, int pkt_type);

bool efa_mock_efa_device_support_unsolicited_write_recv(void);

int efa_mock_ibv_post_recv(struct ibv_qp *qp, struct ibv_recv_wr *wr,
			   struct ibv_recv_wr **bad_wr);

void efa_mock_ibv_wr_rdma_read_save_wr(struct ibv_qp_ex *qp, uint32_t rkey,
				       uint64_t remote_addr);

void efa_mock_ibv_wr_rdma_write_imm_save_wr(struct ibv_qp_ex *qp, uint32_t rkey,
					    uint64_t remote_addr,
					    __be32 imm_data);

struct efa_unit_test_mocks
{
	uint64_t local_host_id;
	uint64_t peer_host_id;
	struct ibv_ah *(*ibv_create_ah)(struct ibv_pd *pd, struct ibv_ah_attr *attr);

	int (*efadv_query_device)(struct ibv_context *ibvctx, struct efadv_device_attr *attr,
							  uint32_t inlen);
#if HAVE_EFADV_CQ_EX

	struct ibv_cq_ex *(*efadv_create_cq)(struct ibv_context *ibvctx,
										 struct ibv_cq_init_attr_ex *attr_ex,
										 struct efadv_cq_init_attr *efa_attr,
										 uint32_t inlen);
#endif

#if HAVE_NEURON
	void *(*neuron_alloc)(void **handle, size_t size);
#endif

#if HAVE_CUDA
	cudaError_t (*ofi_cudaMalloc)(void **ptr, size_t size);
#endif

	ssize_t (*ofi_copy_from_hmem_iov)(void *dest, size_t size,
					  enum fi_hmem_iface hmem_iface, uint64_t device,
					  const struct iovec *hmem_iov,
					  size_t hmem_iov_count, uint64_t hmem_iov_offset);

	int (*efa_rdm_pke_read)(struct efa_rdm_ope *ope);

	ssize_t (*efa_rdm_pke_proc_matched_rtm)(struct efa_rdm_pke *pkt_entry);

	ssize_t (*efa_rdm_ope_post_send)(struct efa_rdm_ope *ope, int pkt_type);

	bool (*efa_device_support_unsolicited_write_recv)(void);

	enum ibv_fork_status (*ibv_is_fork_initialized)(void);

#if HAVE_EFADV_QUERY_MR
	int (*efadv_query_mr)(struct ibv_mr *ibv_mr, struct efadv_mr_attr *attr, uint32_t inlen);
#endif

#if HAVE_EFA_DATA_IN_ORDER_ALIGNED_128_BYTES
	int (*ibv_query_qp_data_in_order)(struct ibv_qp *qp, enum ibv_wr_opcode op, uint32_t flags);
#endif

#if HAVE_EFADV_QUERY_QP_WQS
	int (*efadv_query_qp_wqs)(struct ibv_qp *ibvqp, struct efadv_wq_attr *sq_attr,
				  struct efadv_wq_attr *rq_attr, uint32_t inlen);
#endif

#if HAVE_EFADV_QUERY_CQ
	int (*efadv_query_cq)(struct ibv_cq *ibvcq, struct efadv_cq_attr *attr, uint32_t inlen);
#endif
};

struct ibv_cq_ex *efa_mock_create_cq_ex_return_null(struct ibv_context *context, struct ibv_cq_init_attr_ex *init_attr);

#if HAVE_EFADV_CQ_EX
struct ibv_cq_ex *__real_efadv_create_cq(struct ibv_context *ibvctx,
											struct ibv_cq_init_attr_ex *attr_ex,
											struct efadv_cq_init_attr *efa_attr,
											uint32_t inlen);
uint32_t efa_mock_ibv_read_src_qp_return_mock(struct ibv_cq_ex *current);
uint32_t efa_mock_ibv_read_byte_len_return_mock(struct ibv_cq_ex *current);
uint32_t efa_mock_ibv_read_slid_return_mock(struct ibv_cq_ex *current);
int efa_mock_efadv_wc_read_sgid_return_mock(struct efadv_cq *efadv_cq, union ibv_gid *sgid);
int efa_mock_efadv_wc_read_sgid_return_zero_code_and_expect_next_poll_and_set_gid(struct efadv_cq *efadv_cq, union ibv_gid *sgid);
int efa_mock_ibv_start_poll_expect_efadv_wc_read_ah_and_return_mock(struct ibv_cq_ex *ibvcqx,
																	struct ibv_poll_cq_attr *attr);
int efa_mock_ibv_next_poll_check_function_called_and_return_mock(struct ibv_cq_ex *ibvcqx);
struct ibv_cq_ex *efa_mock_efadv_create_cq_with_ibv_create_cq_ex(struct ibv_context *ibvctx,
																 struct ibv_cq_init_attr_ex *attr_ex,
																 struct efadv_cq_init_attr *efa_attr,
																 uint32_t inlen);
struct ibv_cq_ex *efa_mock_efadv_create_cq_set_eopnotsupp_and_return_null(struct ibv_context *ibvctx,
																		  struct ibv_cq_init_attr_ex *attr_ex,
																		  struct efadv_cq_init_attr *efa_attr,
																		  uint32_t inlen);
#endif

#if HAVE_NEURON
void *__real_neuron_alloc(void **handle, size_t size);
void *efa_mock_neuron_alloc_return_null(void **handle, size_t size);
void *efa_mock_neuron_alloc_return_mock(void **handle, size_t size);
#endif

#if HAVE_CUDA
cudaError_t __real_ofi_cudaMalloc(void **ptr, size_t size);
cudaError_t efa_mock_ofi_cudaMalloc_return_mock(void **ptr, size_t size);
#endif

#if HAVE_EFADV_QUERY_MR
int __real_efadv_query_mr(struct ibv_mr *ibv_mr, struct efadv_mr_attr *attr, uint32_t inlen);
int efa_mock_efadv_query_mr_recv_ic_id_0(struct ibv_mr *ibv_mr, struct efadv_mr_attr *attr, uint32_t inlen);
int efa_mock_efadv_query_mr_rdma_read_ic_id_1(struct ibv_mr *ibv_mr, struct efadv_mr_attr *attr, uint32_t inlen);
int efa_mock_efadv_query_mr_rdma_recv_ic_id_2(struct ibv_mr *ibv_mr, struct efadv_mr_attr *attr, uint32_t inlen);
int efa_mock_efadv_query_mr_recv_and_rdma_read_ic_id_0_1(struct ibv_mr *ibv_mr, struct efadv_mr_attr *attr, uint32_t inlen);
#endif

#if HAVE_EFA_DATA_IN_ORDER_ALIGNED_128_BYTES
int __real_ibv_query_qp_data_in_order(struct ibv_qp *qp, enum ibv_wr_opcode op, uint32_t flags);
int efa_mock_ibv_query_qp_data_in_order_return_0(struct ibv_qp *qp, enum ibv_wr_opcode op, uint32_t flags);
int efa_mock_ibv_query_qp_data_in_order_return_in_order_aligned_128_bytes(struct ibv_qp *qp, enum ibv_wr_opcode op, uint32_t flags);
#endif

#if HAVE_EFADV_QUERY_QP_WQS
int __real_efadv_query_qp_wqs(struct ibv_qp *ibvqp, struct efadv_wq_attr *sq_attr,
			      struct efadv_wq_attr *rq_attr, uint32_t inlen);
int efa_mock_efadv_query_qp_wqs(struct ibv_qp *ibvqp, struct efadv_wq_attr *sq_attr,
				struct efadv_wq_attr *rq_attr, uint32_t inlen);
#endif

#if HAVE_EFADV_QUERY_CQ
int __real_efadv_query_cq(struct ibv_cq *ibvcq, struct efadv_cq_attr *attr, uint32_t inlen);
int efa_mock_efadv_query_cq(struct ibv_cq *ibvcq, struct efadv_cq_attr *attr, uint32_t inlen);
#endif

enum ibv_fork_status __real_ibv_is_fork_initialized(void);

enum ibv_fork_status efa_mock_ibv_is_fork_initialized_return_mock(void);

#endif
