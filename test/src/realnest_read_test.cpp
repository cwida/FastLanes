#include "fastlanes.hpp"
#include "test/tester.hpp"

namespace fastlanes {

// list only
FLS_REALNEST_READ_TEST(3, "aws-public-blockchain-eth-logs")
FLS_REALNEST_READ_TEST(7, "aws-roda-hcls-datalake-gnomad-sites")
FLS_REALNEST_READ_TEST(12, "aws-roda-hcls-datalake-opentargets_latest-cooccurrences")
FLS_REALNEST_READ_TEST(20, "aws-roda-hcls-datalake-opentargets_latest-matches")
FLS_REALNEST_READ_TEST(21, "aws-roda-hcls-datalake-thousandgenomes_dragen-var_partby_samples")
FLS_REALNEST_READ_TEST(23, "daylight-openstreetmap-osm_elements")

// struct only
FLS_REALNEST_READ_TEST(4, "aws-roda-hcls-datalake-clinvar_summary_variants-gene_specific_summary")
FLS_REALNEST_READ_TEST(5, "aws-roda-hcls-datalake-clinvar_summary_variants-hgvs4variation")
FLS_REALNEST_READ_TEST(6, "aws-roda-hcls-datalake-clinvar_summary_variants-submission_summary")
FLS_REALNEST_READ_TEST(8, "aws-roda-hcls-datalake-gtex_8-rnaseqcv1_1_9_gene_tpm")
// FLS_REALNEST_READ_TEST(9, "aws-roda-hcls-datalake-gtex_8-rsemv1_3_0_transcript_expected_count")
FLS_REALNEST_READ_TEST(10, "aws-roda-hcls-datalake-gtex_8-rsemv1_3_0_transcript_tpm")
FLS_REALNEST_READ_TEST(17, "aws-roda-hcls-datalake-opentargets_latest-interaction")
FLS_REALNEST_READ_TEST(25, "gharchive-CommitCommentEvent")
FLS_REALNEST_READ_TEST(30, "gharchive-MemberEvent")

// list/struct combination
FLS_REALNEST_READ_TEST(1, "amazon-berkeley-objects-listings")
FLS_REALNEST_READ_TEST(2, "aws-public-blockchain-btc-transactions")
FLS_REALNEST_READ_TEST(11, "aws-roda-hcls-datalake-opentargets_latest-aotfelasticsearch")
FLS_REALNEST_READ_TEST(13, "aws-roda-hcls-datalake-opentargets_latest-diseasetophenotype")
FLS_REALNEST_READ_TEST(14, "aws-roda-hcls-datalake-opentargets_latest-epmccooccurrences")
FLS_REALNEST_READ_TEST(15, "aws-roda-hcls-datalake-opentargets_latest-failedcooccurrences")
FLS_REALNEST_READ_TEST(16, "aws-roda-hcls-datalake-opentargets_latest-failedmatches")
FLS_REALNEST_READ_TEST(18, "aws-roda-hcls-datalake-opentargets_latest-interactionevidence")
FLS_REALNEST_READ_TEST(19, "aws-roda-hcls-datalake-opentargets_latest-knowndrugsaggregated")
FLS_REALNEST_READ_TEST(22, "cord-19-document_parses")
FLS_REALNEST_READ_TEST(24, "daylight-openstreetmap-osm_features")
FLS_REALNEST_READ_TEST(26, "gharchive-ForkEvent")
FLS_REALNEST_READ_TEST(27, "gharchive-GollumEvent")
FLS_REALNEST_READ_TEST(28, "gharchive-IssueCommentEvent")
FLS_REALNEST_READ_TEST(29, "gharchive-IssuesEvent")
FLS_REALNEST_READ_TEST(31, "gharchive-PullRequestEvent")
FLS_REALNEST_READ_TEST(32, "gharchive-PullRequestReviewCommentEvent")
FLS_REALNEST_READ_TEST(33, "gharchive-PullRequestReviewEvent")
FLS_REALNEST_READ_TEST(34, "gharchive-PushEvent")
FLS_REALNEST_READ_TEST(35, "gharchive-ReleaseEvent")
FLS_REALNEST_READ_TEST(36, "hep-adl-ethz-Run2012B_SingleMu")
FLS_REALNEST_READ_TEST(37, "overturemaps-us-west-2-admins")
FLS_REALNEST_READ_TEST(38, "overturemaps-us-west-2-base")
FLS_REALNEST_READ_TEST(39, "overturemaps-us-west-2-buildings")
FLS_REALNEST_READ_TEST(40, "overturemaps-us-west-2-divisions")
FLS_REALNEST_READ_TEST(41, "overturemaps-us-west-2-places")
FLS_REALNEST_READ_TEST(42, "overturemaps-us-west-2-transportation")
FLS_REALNEST_READ_TEST(43, "twitter-stream-2023-01")

} // namespace fastlanes
